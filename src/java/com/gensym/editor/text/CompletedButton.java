/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CompletedButton.java
 *
 */
package com.gensym.editor.text;


/** Provides the functionality of a TextEditorButton, as well as tracking the
 * events from the parser that indicate whether the text is a complete description
 * of the procedure, rule, etc. that is being edited and so can be accepted.
 * This is the contract on the 'end' button in Classic G2's Text Editor.
 * @author David McDonald
 * @version 1.0
  * @undocumented -- final Text Editor API is still under review
 */
public class CompletedButton extends TextEditorButton implements TextCompleteStatusListener {

  CompletedButton( String label ) {
    super(label);
  }

  /** This is the method that is called to handle TextCompleteStatus events
   * from the Parser. It controls whether the button is en/disabled according
   * to whether the event indicates that the text is or is not complete./
   * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public void checkStatus(TextCompleteStatusEvent e) { 
    //setEnabled( e.getStatus() );
    /* Kneecaped 2/11/98 to implement the decision that this button should
     * always be enabled. (It is enabled by the Session.initializeState().)
     * Keeping the method (and the listener linkage) until the dust settles
     * on the design of the Text Editor's behavior in case it or something
     * like it needs to be resurected. */
  }

}

      
      
