/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Range.java
 *
 */
package com.gensym.editor.text;

/** This is an abstraction of position pairs in the text of the
 * editor. getStart() and getEnd() return between-character
 * indices suitable for setCaretPosition.
 */

// This can be expanded or refined/redefined ad lib. The
// intention is to use this as the basis of a selection
// event where the two values can be fed to setSelection{Start,
// End}. It may want to be reworked as data for Cursors since
// they are what really sustain selection in Java2

public class Range {

  private int start;
  public int getStart() { return start; }
  public void setStart(int s) { start = s; }

  private int end;
  public int getEnd() { return end; }
  public void setEnd(int e) { end = e; }

  public Range (int s, int e) {
    start = s;
    end = e;
  }

  /** Creates a Range with values that are recognized by
   * Range.undefined as consituting a meaningless span.
   * Note that this object can be converted to a meaningful
   * text span by setting its start and end to reasonable
   * values.
   */
  public static Range undefinedRange() {
    return new Range(-1, -1);
  }

  /** Detects ranges that cannot correspond to a meaningful
   * span of text.
   */
  public static boolean undefined(Range r) {
    return ( r.start == -1  &&  r.end == -1 );
  }

}
