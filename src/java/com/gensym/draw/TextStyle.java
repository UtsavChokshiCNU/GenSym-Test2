package com.gensym.draw;

import java.lang.Object;
import java.awt.*;

/*
 *
 * ODTextStyle
 *
 */
public class TextStyle extends Object
{
  protected Font font;
  protected int first_indent;
  protected int subsequent_indent;
  protected int line_spacing;
  protected int lineHeight = USE_JAVA_FONT_METRICS;
  protected int baselineOffset = USE_JAVA_FONT_METRICS;
  protected boolean preferG2CharWidths = false;
  public static final int USE_JAVA_FONT_METRICS = -1;
  

  public TextStyle (Font font, int first_indent,
		    int subsequent_indent,
		    int line_spacing)
  {
    this.font = font;
    this.first_indent = first_indent;
    this.subsequent_indent = subsequent_indent;
    this.line_spacing = line_spacing;
  }

  public TextStyle (Font font, int first_indent,
		    int subsequent_indent,
		    int line_spacing,
		    boolean preferG2CharWidths)
  {
    this.font = font;
    this.first_indent = first_indent;
    this.subsequent_indent = subsequent_indent;
    this.line_spacing = line_spacing;
    this.preferG2CharWidths = preferG2CharWidths;
  }

  public void setBaselineOffset(int baselineOffset)
  {
    this.baselineOffset = baselineOffset;
  }
  
  public void setLineHeight(int lineHeight)
  {
    this.lineHeight = lineHeight;
  }

  public Font getFont() {
    return font;
  }
}


