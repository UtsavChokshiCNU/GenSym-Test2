/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TokenDataEvent.java
 *
 */
package com.gensym.editor.text;


/** A TokenData event encapsulates the information that the other objects
 * in a text editing session might consider useful about the Parser's
 * current (at the time of the event) cursor-token.  It is issued after
 * every ParserInputEvent after the parser has completed its analysis.
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */

class TokenDataEvent extends java.util.EventObject {

  private boolean complete;
  private int index;
  private int startPosition;
  private int endPosition;

  /** Indicates whether the parser believes that the cursor token is
   * complete given the position of the cursor. In most cases, there
   * must be a space after the token for it to be complete, and the
   * cursor must be positioned after that space.
  * @undocumented -- final Text Editor API is still under review
   */
  boolean getComplete()   { return complete; }

  /** Tokens are assigned a index that indicates when they were created
   * during the course of a parse. The number will always increase, but
   * it does not necessarily have any relationship to the order of the
   * tokens that the text has currently be parsed into unless the text
   * has only ever advanced, i.e. no changes or cursor shifts have ever
   * been made to text or positions to the left of the end of the text.
  * @undocumented -- final Text Editor API is still under review
   */
  int getIndex ()         { return index; }

  /** Returns an int that indicates the cursor position just to the
   * left of the first character in the token.
  * @undocumented -- final Text Editor API is still under review
   */
  int getStartPosition () { return startPosition; }

  /** Returns an int that indicates the cursor position justs to the
   * right of the last character in the token. 
  * @undocumented -- final Text Editor API is still under review
   */
  int getEndPosition ()   { return endPosition; }


  TokenDataEvent (G2SideParser source, boolean complete,
		  int index, int start, int end ) {
    super(source);
    this.complete = complete;
    this.index = index;
    startPosition = start;
    endPosition = end;
  }

}
