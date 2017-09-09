/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TextCompleteStatusEvent.java
 *
 */
package com.gensym.editor.text;


/** This event is sent by a G2Parser.  It indicates a change in the status
 * of whether the text that the parser has analyzed is complete.  Usually
 * it is signalling that enough has now been typed to fully define the
 * rule, action, etc. that is being edited. It can, however, be sent more
 * than once in a session if the user continues to extend the text with
 * optional expressions or goes back and modifies earlier parts of what
 * they entered. The event is sent again if this happens, this time with
 * the status false. This cycle may repeat indefinitely.  
 *
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */

public class TextCompleteStatusEvent extends java.util.EventObject {

  private boolean status;
  private Session session;

  /** If the value is true, then the text at that moment constitutes a
   * complete instance of the grammatical category being parsed for.
   * If false, the text is incomplete and will have to be modified or
   * extended before it again becomes complete. 
  * @undocumented -- final Text Editor API is still under review
*/
  public boolean getStatus() { return( status ); }

  /** This returns the editing session that is managing the parsing process
   * that initiated the event. 
  * @undocumented -- final Text Editor API is still under review
  */
  public Session getSession() { return( session ); }


  TextCompleteStatusEvent( G2SideParser source, Session session,
			   boolean status) {
    super(source);
    this.status = status;
    this.session = session;
  }

}

  
