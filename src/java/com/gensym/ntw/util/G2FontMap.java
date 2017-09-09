/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      G2FontMap.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *
 */
package com.gensym.ntw.util;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.draw.G2FontWidths;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.FontMetrics;


/** Translates the G2 symbol for a font into the awt equivalent.
 * The font is sansserif PLAIN, at the point sizes 14, 18, and 24.*/
public class G2FontMap {

  public static final Symbol HM14_ = Symbol.intern("HM14");
  public static final Symbol HM18_ = Symbol.intern("HM18");
  public static final Symbol HM24_ = Symbol.intern("HM24");
  public static final Symbol SMALL_ = Symbol.intern("SMALL");
  public static final Symbol LARGE_ = Symbol.intern("LARGE");
  public static final Symbol EXTRA_LARGE_ = Symbol.intern("EXTRA-LARGE");

  public static final Font HM14, HM18, HM24;

  private static int currentCapacity = 7, numFonts = 3;	// arbitrary
  private static int[] fontSizes = {0, 0, 0, 0, 0, 0, 0};
  private static Font[] fonts    = {null, null, null, null, null, null, null};
  private static final boolean fontDebug = false;

  /** This translates by the canonical G2 font names */
  public static Font get (Symbol g2Font) {
    if (HM14_.equals(g2Font) || SMALL_.equals(g2Font))
      return HM14;
    if (HM18_.equals(g2Font) || LARGE_.equals(g2Font))
      return HM18;
    if (HM24_.equals(g2Font) || EXTRA_LARGE_.equals(g2Font))
      return HM24;
    throw new IllegalArgumentException (g2Font.toString());
  }

  /**
   * Only called for 14, 18, 24 : get () scales other sizes
   */
  private static Font getMatchingFont (final int fontSize) {
    int g2CharWidths = 0;
    int[] g2Widths = null;
    int origFontSize = fontSize;
    int fontSizeLocal = fontSize;
    switch (fontSizeLocal)
      {
      case 14: 
    	  g2Widths = G2FontWidths.HM14; 
    	  break;
      case 18: 
    	  g2Widths = G2FontWidths.HM18; 
    	  break;
      case 24: 
    	  g2Widths = G2FontWidths.HM24; 
    	  break;
      default:
      }
    for (int i=33; i<128; i++)
      g2CharWidths += g2Widths[i];
    int charWidths = Integer.MAX_VALUE;
    Font fnt = null;
    // Get the largest font that fits within the G2 Font
    while (charWidths > g2CharWidths + g2CharWidths/100) { // 1% slop. 
      charWidths = 0;
      Toolkit tkt = Toolkit.getDefaultToolkit ();
      fnt = new Font ("sansserif", Font.PLAIN, fontSizeLocal);
      FontMetrics metrics = tkt.getFontMetrics (fnt);
      for (int i=33; i<128; i++)
	charWidths += metrics.charWidth ((char)i);
      if (fontDebug)
	System.out.println ("For " + fontSizeLocal + " font : G2 = " + g2CharWidths + ", native = " + charWidths);
      fontSizeLocal -= 1;
    }
    if (fontDebug)
      System.out.println ("Returning " + (fontSizeLocal + 1) + " for " + origFontSize);
    cacheFont (origFontSize, fnt);
    return fnt;
  }

  public static Font get (Structure struct, Symbol attrName)
  throws NoSuchAttributeException {
    Symbol g2Font = (Symbol)struct.getAttributeValue(attrName);
    return get(g2Font);
  }

  public static Font get (Structure struct, Symbol attrName, Font defaultFont) {
    Symbol g2Font = (Symbol)struct.getAttributeValue(attrName, null);
    return
      (g2Font == null ?
       defaultFont :
       get(g2Font));
  }

  public static synchronized Font get (int desiredFontSize) {
    for (int i=0; i<numFonts; i++) {
      if (fontSizes[i] == desiredFontSize)
	return fonts[i];
    }
    int matchingFontSize;
    Symbol matchingFontName_;
    if (desiredFontSize >=24)
      matchingFontSize = 24;
    else if (desiredFontSize >= 18)
      matchingFontSize = 18;
    else
      matchingFontSize = 14;
    Font fnt = getMatchingFont (matchingFontSize);
    int actualFontSize = desiredFontSize*fnt.getSize()/matchingFontSize;
    if (fontDebug)
      System.out.println ("Desired FontSize = " + desiredFontSize + ", matching Size = " + matchingFontSize +
			  ", matched Size = " + fnt.getSize() + ", actual FontSize = " + actualFontSize);
    cacheFont (desiredFontSize, new Font ("sansserif", Font.PLAIN, actualFontSize));
    return fnt;
  }

  private static synchronized void cacheFont (int fontSize, Font fnt) {
    ensureCapacity (numFonts + 1);
    fontSizes[numFonts] = fontSize;
    fonts[numFonts++]   = fnt;
  }

  private static synchronized void ensureCapacity (int reqdCapacity) {
    if (currentCapacity > reqdCapacity)
      return;
    currentCapacity *= 2;
    int[] newFontSizes = new int[currentCapacity];
    Font[] newFonts    = new Font[currentCapacity];
    System.arraycopy (fontSizes, 0, newFontSizes, 0, numFonts);
    fontSizes = newFontSizes;
    System.arraycopy (fonts, 0, newFonts, 0, numFonts);
    fonts = newFonts;
  }

  /**
   * Returns 14, 18, or 24, the G2 font size that
   * maps to the actual font size.
   */
  public static int getMatchingG2FontSize (int actualFontSize) {
    Font fnt = get (14);
    if (fnt.getSize() == actualFontSize)
      return 14;
    fnt = get (18);
    if (fnt.getSize() == actualFontSize)
      return 18;
    fnt = get (24);
    if (fnt.getSize() == actualFontSize)
      return 24;
    return -1;
  }

  // The following public static variables should be initialized.
  // This way of doing so is paranoid in the extreme,
  // and the Font.get(Symbol) method should also be changed, but it's
  // late in the cycle, and any change is a chance for a typo.
  // The initializations are done at the end of the file, since
  // getMatchingFont uses various static variables that must
  // be initialized before the method will work. Specifically,
  // the fontSizes array is one, but for safety this goes right at the end
  // Fix for HQ-3014323
  // rpenny 6/18/99 (Oh no, the comment isn't Y2K compliant!)
  static {
  	Font hm14,hm18,hm24;
    try {
      hm14 = getMatchingFont(14);
      hm18 = getMatchingFont(18);
      hm24 = getMatchingFont(24);
    } catch (Exception ex) {
      Trace.exception(ex);
      System.err
          .println("Unable to get accurate matching G2 fonts, using native sizes for 14, 18, and 24 point");
      hm14 = new Font("sansserif", Font.PLAIN, 14);
      hm18 = new Font("sansserif", Font.PLAIN, 18);
      hm24 = new Font("sansserif", Font.PLAIN, 24);
    }
    HM14 = hm14;
    HM18 = hm18;
    HM24 = hm24;
  }
}
