/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TextSource.java
 *
 */
package com.gensym.editor.text;


public interface TextSource {

  /* This is the character sequence that is to be analyzed. */
  public String getText();


  /* This is the position within that string that any reports
   * that arise from the analysis are to be relative to. 
   *
   * The integer that this returns must represent a location between
   * some pair of characters in the text, not the id of a particular 
   * character. Another way of looking at it is that the value of
   * a position is the number of characters to the left of that
   * position in the text. 
   *
   * This character count must be normalized so that any line separators
   * are represented by a single character (e.g. \n), regardless of
   * of how many characters are used in the source from which the
   * text and this position are derived. 
   */
  public int getReferencePosition();

}
