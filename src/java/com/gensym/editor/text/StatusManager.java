/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StatusManager.java
 */
package com.gensym.editor.text;

import java.awt.Color;

import javax.swing.JLabel;

import com.gensym.message.Resource;

/* Translates a package of status information supplied by the parser
 * into updates on a set of views that it manages.  By not committing
 * to what kinds of information there have to be and letting this inter-
 * mediator take up the slack we have the flexibility to change it
 * freely.
 *
 * This object manages two widgets that present the current state of
 * the parse. It learns about that state from ParsingStatusUpdated
 * events, which record whether or not the parse is good at the present
 * point of the parser's cursor, and if not, what is wrong (given
 * as a string) and where it first appreciated the problem, looking
 * from the left end of the text to the right.
 *
 * @author David McDonald
 * @version 1.2 
 */


public class StatusManager implements ParsingStatusUpdatedListener {

  boolean debug = false;

  private static final Resource i18n =
  Resource.getBundle("com.gensym.editor.text.TextEditorLabels");

  boolean currentStatus;

  private Color okColor  = Color.black;
  private Color badColor = Color.red;

  public StatusManager() {
    currentStatus = true;   // true = good.
  }


  /** This method implements the ParsingStatusUpdated Listener.  It has the
   * text that is displayed in the status TextFields that it manages adjusted
   * to fit the new status. */
  @Override
  public void changeParsingStatus(ParsingStatusUpdatedEvent e) {
    if (debug) 
      System.out.println("DDM: status update event:" +
			 "\n             ok? " + e.statusIsOkQ() +
			 "\n  currentStatus: " + currentStatus);

    if ( e.statusIsOkQ() ) {
      setDisplaysToOkState();
      //if ( currentStatus == false ) // this pattern indicates that it used to be bad
      // we used to call the Editor here and tell it to flush the "..."
      // but it's doing that itself now.  Keeping the locus for the timebeing
      // in case there's something else we'd want to do in this situation.
    }
    else
      setDisplaysToBadState( e.getErrorText(), e.getErrorIndex() );
    
    currentStatus = e.getErrorStatus();
  }


  private JLabel statusText;
  /** Returns the TextField that shows whether the parse is grammatical or not */
  public JLabel getStatusText() { return statusText; }
  /** Sets the TextField that shows whether the parse is grammatical or not */
  public void setStatusText(JLabel l) { statusText = l; }


  private JLabel errorText;
  /** Returns the TextField that indicates why the text is ungrammatical if it is. */
  public JLabel getErrorText() { return errorText; }
  /** Sets the TextField that indicates why the text is ungrammatical if it is. */
  public void setErrorText(JLabel f) { errorText = f; }



  private void setDisplaysToOkState() {
    statusText.setText(i18n.getString("ok"));
    statusText.invalidate();
    statusText.setForeground(okColor);
    errorText.setText("");
    errorText.setForeground(okColor);
    statusText.getParent().validate();
  }


  private void setDisplaysToBadState( String text, int index ) {
    if ( index == -1 )
      statusText.setText(i18n.getString("compiler"));  // ? clear enough
    else
      statusText.setText(i18n.getString("bad"));
    if ("".equals(text))
      errorText.setText(i18n.getString("syntaxError"));
    else
      errorText.setText( wrapErrorMsgInHTML(text) );

    errorText.setForeground(badColor);
    statusText.setForeground(badColor);
    statusText.invalidate();
    statusText.getParent().validate();
  }


  private String wrapErrorMsgInHTML(String errorText) {
    String wrappedText =
      "<html> <p> <font color=red>" + errorText + 
      "</font> </p> </html>";
    return wrappedText;
  }
    
}
