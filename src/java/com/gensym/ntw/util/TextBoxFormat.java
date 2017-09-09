
package com.gensym.ntw.util;

import com.gensym.jgi.G2AccessException;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;




/**
 * 
 * TextBoxFormat
 *
 */
public class TextBoxFormat extends Object {
  private static Integer defaultborderwidth = new Integer(2);
  private static Integer defaultlinespacing = new Integer(0);//pbk changed from 2 for attr-display clipping
  private static Integer defaultSubsequentLineIndent = new Integer(8);
  private static Integer defaultLeftMargin = new Integer (4);//new Integer(11);
  private static Integer defaultRightMargin = new Integer (4);//new Integer(11);
  private static Integer defaultFirstLineIndent = new Integer(4);
  private static final Symbol hm14_ = Symbol.intern("HM14");
  private static final Symbol hm18_ = Symbol.intern("HM18");
  private static final Symbol hm24_ = Symbol.intern("HM24");
  private static final Symbol defaultfont = hm14_;
  private static final Symbol defaultlinecolor = Symbol.intern("FOREGROUND");
  private static final Symbol defaultbackgroundcolor = Symbol.intern("TRANSPARENT");
  private static final Symbol defaultbordercolor = Symbol.intern("FOREGROUND");
  private static final Symbol BORDER_COLOR_ = Symbol.intern ("BORDER-COLOR");

  private static final Symbol minimumHeightForTextCell_ = Symbol.intern("MINIMUM-HEIGHT-FOR-TEXT-CELL");
  private static final Symbol mimimumWidthForTextCell_ = Symbol.intern("MINIMUM-WIDTH-FOR-TEXT-CELL");
  private static final Symbol textBoxBottomBorderWidth_ = Symbol.intern("TEXT-BOX-BOTTOM-BORDER-WIDTH");
  private static final Symbol textBoxRightBorderWidth_ = Symbol.intern("TEXT-BOX-RIGHT-BORDER-WIDTH");
  private static final Symbol textBoxTopBorderWidth_ = Symbol.intern("TEXT-BOX-TOP-BORDER-WIDTH");
  private static final Symbol textBoxLeftBorderWidth_ = Symbol.intern("TEXT-BOX-LEFT-BORDER-WIDTH");
  private static final Symbol tableLeftBorderWidth_ = Symbol.intern("TABLE-LEFT-BORDER-WIDTH");
  
  private static final Symbol textBoxMaximumFormatWidthForTextCell_ = Symbol.intern("MAXIMUM-FORMAT-WIDTH-FOR-TEXT-CELL");
  private static final Symbol minimumFormatWidthForTextCell_ = Symbol.intern("MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL");
  private static final Symbol textCellTurnoverLineIndentation_ = Symbol.intern("TEXT-CELL-TURNOVER-LINE-INDENTATION");
  private static final Symbol textCellParagraphIndentation_ = Symbol.intern("TEXT-CELL-PARAGRAPH-INDENTATION");
  private static final Symbol maximumWordSpacing_ = Symbol.intern("MAXIMUM-WORD-SPACING");
  private static final Symbol minimumWordSpacing_ = Symbol.intern("MINIMUM-WORD-SPACING");
  private static final Symbol defaultWordSpacing_ = Symbol.intern("DEFAULT-WORD-SPACING");
  private static final Symbol textCellLineSpacing_ = Symbol.intern("TEXT-CELL-LINE-SPACING");
  private static final Symbol textCellBaselineSpacing_ = Symbol.intern("TEXT-CELL-BASELINE-POSITION");
  private static final Symbol textCellLineHeight_ = Symbol.intern("TEXT-CELL-LINE-HEIGHT");
  private static final Symbol textCellBottomMargin_ = Symbol.intern("TEXT-CELL-BOTTOM-MARGIN");
  private static final Symbol textCellRightMargin_ = Symbol.intern("TEXT-CELL-RIGHT-MARGIN");
  private static final Symbol textCellTopMargin_ = Symbol.intern("TEXT-CELL-TOP-MARGIN");
  private static final Symbol textCellLeftMargin_ = Symbol.intern("TEXT-CELL-LEFT-MARGIN");
  private static final Symbol textCellFontMap_ = Symbol.intern("TEXT-CELL-FONT-MAP");
  private static final Symbol textCellBackgroundColorQ_ = Symbol.intern("TEXT-CELL-BACKGROUND-COLOR?");
  private static final Symbol textCellLineColorQ_ = Symbol.intern("TEXT-CELL-LINE-COLOR?");
  private static final Symbol TEXT_CELL_FONT_MAP_ = Symbol.intern ("TEXT-CELL-FONT-MAP");
  //  private static final Symbol leftMargin_ = Symbol.intern("LEFT-MARGIN");
  //  private static final Symbol rightMargin_ = Symbol.intern("RIGHT-MARGIN");
  //  private static final Symbol firstLineIndent_ = Symbol.intern("FIRST-LINE-INDENT");
  //  private static final Symbol subsequentLineIndent_ = Symbol.intern("SUBSEQUENT-LINE-INDENT");

  private Structure data;

  public TextBoxFormat(Structure data) {
    this.data = data;
    if (this.data == null) {
      System.out.println("TEXT BOX FORMAT DATA was NULL");
      this.data = new Structure();
    }
  }
  
  public Symbol getTextLineColor() {
    return (Symbol) data.getAttributeValue(textCellLineColorQ_,
					   defaultlinecolor);
  }

  public Symbol getTextBackgroundColor() {
    return (Symbol) data.getAttributeValue(textCellBackgroundColorQ_,
					   defaultbackgroundcolor);
  }

  public static final Symbol
  //attribute-display-table-format
  ATTRIBUTE_DISPLAY_VALUE_FORMAT_
  = Symbol.intern ("ATTRIBUTE-DISPLAY-VALUE-FORMAT"),
    LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_
  = Symbol.intern ("LARGE-ATTRIBUTE-DISPLAY-VALUE-FORMAT"),
    EXTRA_LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-ATTRIBUTE-DISPLAY-VALUE-FORMAT"),
    SMALL_ATTRIBUTE_DESCRIPTION_FORMAT_
  = Symbol.intern ("SMALL-ATTRIBUTE-DESCRIPTION-FORMAT"),
    ATTRIBUTE_DESCRIPTION_FORMAT_//attr-tables
  = Symbol.intern ("ATTRIBUTE-DESCRIPTION-FORMAT"),
    EXTRA_LARGE_ATTRIBUTE_DESCRIPTION_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-ATTRIBUTE-DESCRIPTION-FORMAT"),
    SMALL_ATTRIBUTE_VALUE_FORMAT_
  = Symbol.intern ("SMALL-ATTRIBUTE-VALUE-FORMAT"),
    ATTRIBUTE_VALUE_FORMAT_
  = Symbol.intern ("ATTRIBUTE-VALUE-FORMAT"),
    EXTRA_LARGE_ATTRIBUTE_VALUE_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-ATTRIBUTE-VALUE-FORMAT"),
    SMALL_CLASS_FORMAT_
  = Symbol.intern ("SMALL-CLASS-FORMAT"),
    CLASS_FORMAT_ = Symbol.intern ("CLASS-FORMAT"),
    EXTRA_LARGE_CLASS_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-CLASS-FORMAT"),
    EXTRA_LARGE_MESSAGE_FORMAT_
  = Symbol.intern ("EXTRA-LARGE-MESSAGE-FORMAT"),
    SMALL_STATEMENT_FORMAT_
  = Symbol.intern ("SMALL-STATEMENT-FORMAT"),
    SMALL_FREE_TEXT_FORMAT_
  = Symbol.intern ("SMALL-FREE-TEXT-FORMAT"),
    SMALL_BORDERLESS_FREE_TEXT_FORMAT_
  = Symbol.intern ("SMALL-BORDERLESS-FREE-TEXT-FORMAT");
  private static Hashtable lineHeights = new Hashtable(23);
  static {
    lineHeights.put(ATTRIBUTE_DISPLAY_VALUE_FORMAT_ , new Integer(14));//15 in g2//11
    lineHeights.put(LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_, new Integer(18));// 14
    lineHeights.put(EXTRA_LARGE_ATTRIBUTE_DISPLAY_VALUE_FORMAT_, new Integer(25));// 20
    //lineHeights.put(SMALL_ATTRIBUTE_DESCRIPTION_FORMAT_, new Integer(15));//18 in g2//14
    //lineHeights.put(ATTRIBUTE_DESCRIPTION_FORMAT_, new Integer(20));//16
    //lineHeights.put(EXTRA_LARGE_ATTRIBUTE_DESCRIPTION_FORMAT_, new Integer(26));//21
    //lineHeights.put(SMALL_ATTRIBUTE_VALUE_FORMAT_, new Integer(18));//14
    //lineHeights.put(ATTRIBUTE_VALUE_FORMAT_, new Integer(20));//16
    //lineHeights.put(EXTRA_LARGE_ATTRIBUTE_VALUE_FORMAT_, new Integer(26)); //21
    //lineHeights.put(SMALL_CLASS_FORMAT_, new Integer(18));//14
    //lineHeights.put(CLASS_FORMAT_, new Integer(20));//16
    //lineHeights.put(EXTRA_LARGE_CLASS_FORMAT_, new Integer(26)); //21
    //lineHeights.put(EXTRA_LARGE_MESSAGE_FORMAT_, new Integer(30));//24
    //lineHeights.put(SMALL_STATEMENT_FORMAT_, new Integer(15));//12
    //lineHeights.put(SMALL_FREE_TEXT_FORMAT_, new Integer(15));//13
    //lineHeights.put(SMALL_BORDERLESS_FREE_TEXT_FORMAT_, new Integer(15));//13
    //java is 16, 21, 27
    //most of g2 is 18, 20, 26
  }
  
  public static int getLineHeight(Symbol formatType)
  {
    Integer lineHeight = null;
    if (formatType != null)
      lineHeight =(Integer) lineHeights.get(formatType);
    if (lineHeight != null)
      return lineHeight.intValue();
    else
      return com.gensym.draw.TextStyle.USE_JAVA_FONT_METRICS;
  }

  public int getLineHeight()
  {
    Integer lineHeight = (Integer)data.getAttributeValue(textCellLineHeight_, null);
    if (lineHeight == null)
      return com.gensym.draw.TextStyle.USE_JAVA_FONT_METRICS;
    else
      return
	lineHeight.intValue();
  }
  
  public int getBaselineOffset()
  {
    Integer BaselineOffset = (Integer)data.getAttributeValue(textCellBaselineSpacing_, null);
    if (BaselineOffset == null)
      return com.gensym.draw.TextStyle.USE_JAVA_FONT_METRICS;
    else
      return BaselineOffset.intValue();
  }
  
  public Symbol getTextBorderColor() {
    return (Symbol) data.getAttributeValue(BORDER_COLOR_,
					   defaultbordercolor);
  }

  public Integer getTextBorderWidth() {
    return (Integer) data.getAttributeValue(textBoxLeftBorderWidth_,//pick one
					    defaultborderwidth);
  }

  public Integer getTableBorderWidth() {
    return (Integer) data.getAttributeValue(tableLeftBorderWidth_,//pick one
					    defaultborderwidth);
  }

  public Integer getTextLineSpacing() {
    return (Integer) data.getAttributeValue(textCellLineSpacing_,
					    defaultlinespacing);
  }

  public Symbol getFont() {
    //System.out.println("FORMAT DATA is " + data);
    return (Symbol) data.getAttributeValue(TEXT_CELL_FONT_MAP_, defaultfont);
  }

  public static int g2FontToFontsize(Symbol g2font) {
    if (g2font == hm18_)
      return 18;
    else if (g2font == hm14_)
      return 14;
    else if (g2font == hm24_)
      return 24;
    else
      return 14;
  }
  
  public Integer getLeftMargin() {
    return (Integer) data.getAttributeValue(textCellLeftMargin_, defaultLeftMargin);
  }

  public Integer getRightMargin() {
    return (Integer) data.getAttributeValue(textCellRightMargin_, defaultRightMargin);
  }

  public Integer getFirstLineIndent() {
    return (Integer) data.getAttributeValue(textCellParagraphIndentation_, defaultFirstLineIndent);
  }

  public Integer getSubsequentLineIndent() {
    return (Integer) data.getAttributeValue(textCellTurnoverLineIndentation_, defaultSubsequentLineIndent);
  }

  public int getMinimumFormatWidth()
  {
    Object attrValue = data.getAttributeValue(minimumFormatWidthForTextCell_, null);
    if (attrValue != null)
      return ((Integer)attrValue).intValue();
    else
      return 400;
  }

  public int getTopMargin()
  {
    Object attrValue = data.getAttributeValue(textCellTopMargin_, null);
    if (attrValue != null)
      return ((Integer)attrValue).intValue();
    else
      return 0;
  }

  public int getBottomMargin()
  {
    Object attrValue = data.getAttributeValue(textCellBottomMargin_, null);
    if (attrValue != null)
      return ((Integer)attrValue).intValue();
    else
      return 0;
  }

  public String dumpInternals()
  {
    return data.toString();
  }

}
