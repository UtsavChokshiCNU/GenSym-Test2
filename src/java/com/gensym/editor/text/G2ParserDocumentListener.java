/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ParserDocumentListener.java
 *
 */
package com.gensym.editor.text;

import javax.swing.text.Document;
import javax.swing.text.BadLocationException;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.CaretEvent;

/** This listens to add and remove DocumentEvents, packages up
 * the corresponding ParserInputEvent, and sends it to the
 * ParserInputEventListener that was assigned to it in its
 * constructor. 
 *
 * The method setDebug(true) will turn on standard-output traces
 * that will show what texts and locations were given in the
 * DocumentEvents.
 *
 * Somewhat surprisingly, we have been unable to get a changedUpdate
 * to fire, only adds and removes, even when we do overwrites on 
 * selected texts. 
 */

/*xo Version of 6/00 -- ddm
 */
public class G2ParserDocumentListener implements DocumentListener, CaretListener {

  private boolean debug = false;
  public void setDebug(boolean state) { debug = state; }

  public G2ParserDocumentListener(ParserInputEventListener l) {
    this.l = l;
  }

  //--- passing events on out to the parser
  private String entireText = "";

  private ParserInputEventListener l;

  protected void send(ParserInputEvent e) {
    if (debug) 
      System.out.println("Sending " + e);
    switch ( e.getID() ) {
    case ParserInputEvent.CURSOR_CHANGE:
      l.cursorPositionChanged(e);
      break;
    case ParserInputEvent.ADDED_CHARACTER:
      l.characterAdded(e);
      break;
    case ParserInputEvent.DELETED_CHARACTER:
      l.characterDeleted(e);
      break;
    case ParserInputEvent.ADDED_REGION:
      l.regionAdded(e);
      break;
    case ParserInputEvent.DELETED_REGION:
      l.regionDeleted(e);
      break;
    case ParserInputEvent.REPLACED_REGION:
      l.regionReplaced(e);
      break;
    case ParserInputEvent.REPLACED_UNEQUAL_REGIONS:
      l.replacedUnEqualRegions(e);
      break;
    case ParserInputEvent.NO_CHANGE:
      break;
    }
  }


  private int eventType = ParserInputEvent.NO_CHANGE;

  private boolean ignore = false;
  @Override
  public void insertUpdate(DocumentEvent e) {
    ignore = true;
    if (debug)
      System.out.println("Heard an insert of " + e.getLength() + " characters" +
			 " at " + e.getOffset() );
    Document doc = e.getDocument();
    int start = e.getOffset();
    int end = start + e.getLength();
    String delta = "";
    try {
      delta = doc.getText(start, e.getLength());
      if (debug)
	System.out.println("Heard addition of \"" + delta + "\"");
      entireText = doc.getText(0, doc.getLength());
      if (debug)
	System.out.println("  on \"" + entireText + "\"");
    } catch (BadLocationException ex) {
      System.err.println("Bad location while updating the document cache: " +
			 ex.offsetRequested());
    }
    if ( delta.length() > 1 )
      eventType = ParserInputEvent.ADDED_CHARACTER;
    else
      eventType = ParserInputEvent.ADDED_REGION;

    send( new ParserInputEvent( (Object)this, // source
				delta, // string that was added
				start, //  where the insertion occurred
				end, // new cursor position
				start, // old cursor position
				true, // really send the character to G2
				eventType, // the kind of parser input event
				entireText ));
  }

  @Override
  public void removeUpdate(DocumentEvent e) {
    ignore = true;
    if (debug)
      System.out.println("Heard a remove of " + e.getLength() + " characters" +
			 " at " + e.getOffset() );
       
    int leftEnd = e.getOffset();
    int rightEnd = leftEnd + e.getLength();
    String delta = entireText.substring(e.getOffset(), e.getOffset() + e.getLength());
    Document doc = e.getDocument();    
    try {
      entireText = doc.getText(0, doc.getLength());
      if (debug)
	System.out.println("  on \"" + entireText + "\"");
    } catch (BadLocationException ex) {
      System.err.println("Bad location while updating the document cache: " +
			 ex.offsetRequested());
    }    
    if (debug)
      System.out.println("Heard removal of \"" + delta + "\"");

    if ( delta.length() > 1 )
      eventType = ParserInputEvent.DELETED_CHARACTER;
    else
      eventType = ParserInputEvent.DELETED_REGION;

    send( new ParserInputEvent( (Object)this, // source
				delta, // string that was deleted
				leftEnd, // where the deletion occurred (result cursorpos)
				leftEnd, // new cursor position
				rightEnd, // old cursor position
				true, // really send the character to G2
				eventType, // the kind of parser input event
				entireText ));
  }

  @Override
  public void changedUpdate(DocumentEvent e) {
    if (debug)
      System.out.println("Heard a change of " + e.getLength() + " characters" +
			 " at " + e.getOffset() );
  }

  private int lastCaretPosition = 0;
  @Override
  public void caretUpdate(CaretEvent e) {
    int newCaretPosition = e.getDot();
    if (!ignore) {
      Document doc = ((javax.swing.text.JTextComponent)e.getSource()).getDocument();
      try {
	entireText = doc.getText(0, doc.getLength());
	if (debug)
	  System.out.println("  on \"" + entireText + "\"");
      } catch (BadLocationException ex) {
	System.err.println("Bad location while updating the document cache: " +
			   ex.offsetRequested());
      }    
    //System.out.println("CARET MOVED");          
      //System.out.println("sending CARET MOVED");    
      send(new ParserInputEvent((Object)this, // source
				newCaretPosition,
				lastCaretPosition,
				true, // really send the character to G2
				entireText));
    }
    lastCaretPosition = newCaretPosition;
    ignore = false;
  }
}
