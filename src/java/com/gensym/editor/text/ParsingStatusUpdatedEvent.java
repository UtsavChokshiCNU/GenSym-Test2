/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ParsingStatusUpdatedEvent.java
 *
 */
package com.gensym.editor.text;


/** This event contains the information that the G2 Parser supplies
 * as to the conclusions it has drawn about the text as of the last
 * ParserInputEvent issued by the text source. It is issued as soon
 * has the parser has finished its analysis of the text given that
 * input event. 
 *
 * @author David McDonald
 * @version 1.0
 */
public class ParsingStatusUpdatedEvent extends java.util.EventObject {

  private Session session;
  private boolean status;
  private int errorIndex;
  private String errorText;

  public static final int NoErrorIndex = -1;


  /* This constructor is for when the status is ok. 
   */
  ParsingStatusUpdatedEvent(G2SideParser source, Session session,
			    boolean newStatusIsOK) {
    super(source);
    this.session = session;
    status = newStatusIsOK;  // This will always be true baring a bug in the caller.
    errorIndex = NoErrorIndex;
    errorText = "";
  }


  /* This constructor is for when the status becomes bad. */
  ParsingStatusUpdatedEvent(G2SideParser source, Session session,
			    boolean newStatusIsBad, int errorIndex, String errorText) {
    super(source);
    status = newStatusIsBad;       // will always be false
    this.errorIndex = errorIndex;
    this.errorText = errorText;
  }


  /** This variable indicates whether the text is grammatical (true) or not (false) at
   * the time the event is issued.
   */
  public boolean statusIsOkQ() { return( status ); }


  /** If false, there is no error index data */
  public boolean validErrorIndex() { return ( errorIndex != NoErrorIndex ); }


  /** Provides a backpoint that can be used to distinguish the status of one
   * editing session vs. another when a single listerner is tracking multiple
   * editing sessions.
   */
  public Session getSession() { return( session ); }

  /** If the text is ungrammatical, this will return false; if grammatical, true.
   * It is providing the same information as statusIsOKQ, but as an accessor.
   */
  public boolean getErrorStatus() {  return( status ); }

  /** If the text is ungrammatical, the int this returns indicates the cursor 
   * position at which the parse first noted the problem (parsing from left
   * to right).  If the text is grammatical, it returns -1. If the text was
   * grammatical but rejected by the compiler when doing a conclude, then
   * statusIsOkQ will return false and this will again return -1 since there
   * is no way to identify  the location within the text that is responsible 
   * for the problem.
   */
  public int getErrorIndex() { return( errorIndex ); }

  /**  If the text is ungrammatical, this returns a String that describes what
   * the problem is.  If the text is grammatical, it returns an empty string ("").
   */
  public String getErrorText() { return( errorText ); }
  
}


