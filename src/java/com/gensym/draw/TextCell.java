package com.gensym.draw;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Toolkit;

/**
 *
 * TextCell
 *
 */
public class TextCell extends Object
{
  private String textString;
  private TextStyle style;

  public static final int LEFT   = 0;
  public static final int CENTER = 1;
  public static final int RIGHT  = 2;

  private int textJustification = LEFT;

  private Color textColor = Color.black;
  private Color backgroundColor = Color.white;
  private Color borderColor = Color.green;
  private int borderWidth = 0;
  private boolean borderHasPositiveWidth = false;
  private boolean drawBorder = false; 
  private boolean drawBackground = false;
  private boolean drawText = true;
  private TextLine startLine = null;
  private TextLine endLine = null;
  private Rectangle bounds;
  protected int width;
  protected int height;
  private int cellHeight;
  private int formatHeight = -1;
  private int topMargin = 0;
  private int bottomMargin = 0;
  private int leftMargin = 0;
  private int rightMargin = 0;
  private boolean textcelldebugp = false;

  

  public TextCell(final int width, 
		  final String text, final TextStyle style,
		  final Color background_color,
		  final Color text_color,
		  final int border_width,
		  final Color border_color)
  {
	String textValue = text;  
    if (textValue != null)
      textValue = textValue.replace ((char)45, (char)173);
    textString = textValue;
    this.style = style;
    this.backgroundColor = background_color;
    this.textColor = text_color;
    initializeBorder(border_width, border_color);
    int formatWidth = width - (Math.max(borderWidth,leftMargin) + 
			       Math.max(borderWidth,rightMargin));

    initializeText(textString, formatWidth);
    
    initializeBounds(width);
  }
  

  private void initializeBorder(int border_width, Color border_color) {
    this.borderColor = border_color;
    this.borderWidth = Math.max(0,border_width);
    if (borderWidth > 0) {
    	borderHasPositiveWidth = true;
    }
    else if (textcelldebugp && borderWidth < 0)
      System.out.println("BORDER WAS < 0\n");
  }

  private void initializeText(String text, int format_width){
    if (text == null)
      return;
    
    if (textcelldebugp)
      System.out.println("calling initializeText "+format_width);
    String line;
    Paragraph previous_paragraph = null;
    Paragraph paragraph;
    char[] chars = text.toCharArray();
    int i = 0, len = chars.length, nextStart = 0;
    boolean afterNewline = true;
    if (textcelldebugp)
      System.out.println("Paragraph Break loop start"+text);

    if (len == 0) {
      // special case: "". don't mess up the following loop to deal with
      // this case
      paragraph = new Paragraph(text,
				style.font,
				format_width,
				style.first_indent, 
				style.subsequent_indent,
				style.preferG2CharWidths);
      startLine = paragraph.startLine;
      endLine = paragraph.endLine;
      return;
    }
      
    for (i = 0; i<len ; i++)
      {
	char ch = chars[i];
	if (ch == '\n' || ch == '\r' || i == (len - 1))
	  {
	    if (ch == '\n' || ch == '\r')
	      line = text.substring(nextStart,i);
	    else
	      line = text.substring(nextStart,i+1);
	    nextStart = i+1; // skip that bad-old \n
	    if (textcelldebugp)
	      System.out.println("unfrmtd pgraph text: "+line+
				 " desired width "+format_width);
	    paragraph = new Paragraph(line,
				      style.font,
				      format_width,
				      style.first_indent, 
				      style.subsequent_indent,
				      style.preferG2CharWidths);
	    if (previous_paragraph == null)
	      startLine = paragraph.startLine;
	    else
	      previous_paragraph.linkNext(paragraph);
	    previous_paragraph = paragraph;
	    endLine = paragraph.endLine;
	  }
      }
  }

  private FontMetrics metrics;
  private void initializeBounds(int width) {
    Toolkit defaultToolkit = Toolkit.getDefaultToolkit();
    if (metrics == null)
      metrics = defaultToolkit.getFontMetrics(style.font);
    int cell_height = computeCellHeight(metrics);
    this.cellHeight = cell_height;
    this.width = width;
    this.bounds=new Rectangle(0,0,width,cellHeight);
    recomputeHeight();
  }

  private int computeCellHeight(FontMetrics metrics) {
    TextLine line = startLine;
    Paragraph paragraph;
    int line_top = 0; /* was y */
    int baseline_offset = metrics.getAscent() + style.line_spacing;
    int line_height = baseline_offset + metrics.getDescent();
    while (line != null)
      {
	paragraph = line.paragraph;
	line_top += line_height;
	line = line.next;
      }
    return line_top;
  }

  private void recomputeHeight() {
    this.height = cellHeight + topMargin + bottomMargin;
    this.bounds.height = this.height;
  }

  
  private void drawBackground(Graphics g) {
    g.setColor(backgroundColor);
    g.fillRect(0,0,width,height);
  }

  private void drawString (final Graphics g, final String string,
		  final int left, final int top,
		  final int indent,
		  final int justification,
		  final int containerWidth) {
	
	int leftIndex = left;
    if (justification == LEFT) {
      g.drawString(string,leftIndex + indent + leftMargin,top);
    } else {
      int charCount = string.length();
      FontMetrics fontMetrics = g.getFontMetrics();
      int stringWidth = 0;
      char currentChar;
      for (int i=0;i<charCount;i++) {
	currentChar = string.charAt(i);
	stringWidth = stringWidth + fontMetrics.charWidth(currentChar);
      }
      if (justification == CENTER)
 	leftIndex = leftIndex + ((containerWidth-stringWidth)/2);
      else { //right
	leftIndex = (leftIndex + Math.max(leftMargin,(containerWidth-stringWidth)-rightMargin));
      }
      g.drawString(string,leftIndex,top);
    }
  }

  private void drawText(Graphics g, int shift_x, int shift_y) {
    g.setFont(style.font);
    g.setColor(textColor);
    TextLine line = startLine;
    Paragraph paragraph;
    FontMetrics fontMetrics = g.getFontMetrics();

    int line_top = 0;
    int baseline_offset = style.baselineOffset;
    if (baseline_offset == TextStyle.USE_JAVA_FONT_METRICS)
      baseline_offset = fontMetrics.getAscent();
    if (textcelldebugp)
      System.out.println("BASELINE_OFFSET = " + baseline_offset);
    int line_height = style.lineHeight;
    if (line_height == TextStyle.USE_JAVA_FONT_METRICS) {
      int descent = fontMetrics.getDescent();
      line_height = baseline_offset + descent;
    }
    while (line != null)
      {
	
	paragraph = line.paragraph;
	int indent
	  = (line.equals(paragraph.startLine)) ?
	  paragraph.firstIndent :
	  paragraph.subsequentIndent;
	drawString (g,line.text,
		    shift_x,
		    shift_y + line_top + baseline_offset, 
		    indent,
		    textJustification,
		    width);
	line_top += (line_height + style.line_spacing);
	line = line.next;
      } 
  }

  private void drawBorder(Graphics g) {
    if (textcelldebugp)
      System.out.println("DRAWING THE BORDER\n");
    g.setColor(borderColor);
    g.fillRect(0,0, width, borderWidth);
    g.fillRect(width - borderWidth, 0, borderWidth, height);
    g.fillRect(0, height - borderWidth, width, borderWidth);
    g.fillRect(0,0,borderWidth, height);
  }

  TextStyle getTextStyle()
  {
    return style;
  }


  /**
   * @deprecated pass in a Component instead.
   * @see #format(Component)
   */
  public void format(Graphics graphics) {
     graphics.setFont(style.font);
     FontMetrics fontMetrics = graphics.getFontMetrics();
     format(fontMetrics);
  }

  private void format(FontMetrics metrics) {
    if (textcelldebugp)
      System.out.println("called format on text box, startLine = "+startLine);
    if (startLine == null) 
      {
	formatHeight = 0;
	return;
      }
    
    TextLine line = startLine;
    TextLine nextStartLine = null;
    if (textcelldebugp) {
      System.out.println("in tbox format metrics="+metrics);
      System.out.flush();
    }

    Paragraph first_paragraph = line.paragraph;
    Paragraph paragraph = line.paragraph;
    Paragraph previous_paragraph = null;
    
    while (paragraph != null)
    {
      nextStartLine = paragraph.endLine.next;
      paragraph.endLine.next = null;
      if (textcelldebugp)
	{
	  System.out.println("format p before");
	  paragraph.dump(System.out);
	}
      paragraph.format(metrics);
      if (textcelldebugp)
	{
	  System.out.println("format p after");
	  paragraph.dump(System.out);
	}
      if (previous_paragraph != null)
          previous_paragraph.linkNext(paragraph);
      previous_paragraph = paragraph;
      if (nextStartLine != null)
          paragraph = nextStartLine.paragraph;
        else
          paragraph = null;
    }

    if (textcelldebugp)
      System.out.println("end outer loop");
    startLine = first_paragraph.startLine;
    endLine = previous_paragraph.endLine;
    
    formatHeight = computeCellHeight(metrics);
    this.cellHeight = formatHeight;
    recomputeHeight();
  }

  /** Lays out the cell for the <code>component</code>.
   */
  public void format(Component component)
  {
    FontMetrics fontMetrics = component.getFontMetrics(style.font);
    format(fontMetrics);
  }
  
  public void setTextJustification(int justification) {
    textJustification = justification;
  }
  
  public void setTextColor(Color textColor) {
    this.textColor = textColor;
  }

  public Color getTextColor() {
    return textColor;
  }

  public void setBackgroundColor(Color backgroundColor) {
    this.backgroundColor = backgroundColor;
  }

  public void setBorderColor(Color borderColor) {
    this.borderColor = borderColor;
  }

  public void setReverseVideo() {
    Color tmp = textColor;
    textColor = backgroundColor;
    backgroundColor = tmp;
  }
  
  public void setBorderWidth(int width) {
    this.borderWidth = width;
    this.borderHasPositiveWidth = (borderWidth>0);
  }
      
  public void setDrawBorder(boolean drawBorder) {
    this.drawBorder = drawBorder;
  }

  public void setDrawBackground(boolean drawBackground) {
    this.drawBackground = drawBackground;
  }

  public boolean getDrawBackground() {
    return drawBackground;
  }
  
  public void setDrawText(boolean drawText) {
    this.drawText = drawText;
  }

  public boolean isDrawText() {
    return drawText;
  }

  public Font getFont()
  {
    return style.font;
  }

  public void setFont(Font font)
  {
    style.font = font;
  }
  
  public int getHeight() {
    if (textcelldebugp)
      System.out.println(bounds.height + "<==BOUNDS-HEIGTH CELL-HEIGHT ==>" + cellHeight);
    return bounds.height;
  }

  public int getFormattedHeight()
  {
    if (formatHeight == -1)
      throw new IllegalStateException("Text cell must be formatted");
    else
      return formatHeight;
  }

  public void setHeight(int height) {
    this.height = height;
    this.cellHeight = height;
    bounds.height = height;
  }
  
  public int getWidth() {
    return bounds.width;
  }

  public int getRightMargin() {
    return rightMargin;
  }

  public int getLeftMargin() {
    return leftMargin;
  }
  
  public int getTopMargin() {
    return topMargin;
  }

  public int getBottomMargin() {
    return bottomMargin;
  }
  
  public void setTopMargin(int margin) {
    if (textcelldebugp)
      System.out.println("setting top margin in cell to " + margin);
    if (margin != topMargin) {
      this.topMargin = margin;
      recomputeHeight();
    }
  }

  private int calculateFormatWidth()
  {
    // return (width - (2 * borderWidth) - (leftMargin + rightMargin));
    return width - (Math.max(borderWidth,leftMargin) + 
		    Math.max(borderWidth,rightMargin));
  }

  public void setRightMargin(int margin) {
    this.rightMargin = margin;
    if (textcelldebugp)
      System.out.println("setRM width compute width = "+width+
			 " computed "+calculateFormatWidth());
    initializeText(textString, calculateFormatWidth());
  }
  
  public void setLeftMargin(int margin) {
    this.leftMargin = margin;
    if (textcelldebugp)
      System.out.println("setLM width compute width = "+width+
			 " computed "+calculateFormatWidth());
    initializeText(textString, calculateFormatWidth());
  }

  public void setBottomMargin(int margin) {
    if (margin != bottomMargin) {
      this.bottomMargin = margin;
      recomputeHeight();
    }
  }
  
  public boolean inside(int logical_x, int logical_y)
  {
     return bounds.contains(logical_x,logical_y);
  }
  
  public void draw (Graphics outer_g, int shift_x, int shift_y)
  {
     Graphics g = outer_g.create(shift_x ,shift_y,width,height);
     if (drawBackground)
       drawBackground(g);
     if (drawText) 
       drawText(g, 0, topMargin);
     if (textcelldebugp)
       System.out.println("TEXT-CELL-DRAW-TEXT topMargin = " + topMargin);
     if (drawBorder&&borderHasPositiveWidth) 
       drawBorder(g);
     g.dispose();
  }

  public Rectangle bounds()
  {
     return bounds;
  }

  public void setText(final String text) {
	String textValue = text;
    if (textValue != null)
      textValue = textValue.replace ((char)45, (char)173);
    textString = textValue;
    if (textcelldebugp)
      System.out.println("setTxt width compute width = "+width+
			 " computed "+calculateFormatWidth());

    initializeText(textString, calculateFormatWidth());
    initializeBounds(width);
  }

  public String getText() {
    return textString;
  }

  public void setWidth(int newWidth) {
    width = newWidth;
    if (textcelldebugp)
      System.out.println("setWidth width compute width = "+width+
			 " computed "+calculateFormatWidth());
    initializeText(textString,calculateFormatWidth());
    initializeBounds(width);
  }

  @Override
  public String toString()
  {
    return textString;
  }

  public void dispose() {
    this.bounds = null;
    this.endLine = null;
    this.startLine = null;
    this.textString = null;
    this.style = null;
  }

}
