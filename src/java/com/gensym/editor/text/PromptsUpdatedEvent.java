/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptsUpdatedEvent.java
 *
 */
package com.gensym.editor.text;

import java.util.EventObject;
import com.gensym.editor.text.Session;
import com.gensym.util.Sequence;


/** This event is issued by the Parser when it has processed a
 * ParserInputEvent that resulted in a change to the current
 * set of prompts. It incorporates the new prompts as separate
 * fields containing string arrays and a pointer to the input
 * event that mandated the change.
 *
 * @author David McDonald
 * @version 2.0 5/00
 * @undocumented -- final Text Editor API is still under review
 */
public class PromptsUpdatedEvent  extends EventObject {

  private ParserInputEvent event;
  private String[] completionPrompts;
  private String[] categoryPrompts;

  PromptsUpdatedEvent(G2SideParser parser, ParserInputEvent e, String[] completion, String[] category) {
    super(parser);
    event = e;
    completionPrompts = completion;
    categoryPrompts = category;
  }


  /** Returns the current completion prompts as an array of strings
   * sorted alphabetically.
   * @undocumented -- final Text Editor API is still under review
   */
  public String[] getCompletionPrompts() { return completionPrompts; }


  /** Returns the current category prompts as an array of strings
   * sorted alphabetically.
   * @undocumented -- final Text Editor API is still under review
   */
  public String[] getCategoryPrompts() { return categoryPrompts; }


  /** Returns the ParserInputEvent that put the parser into a state
   * where a new set of prompts applied.
   * @undocumented -- final Text Editor API is still under review
   */
  public ParserInputEvent getParserInputEvent() { return event; }

}
