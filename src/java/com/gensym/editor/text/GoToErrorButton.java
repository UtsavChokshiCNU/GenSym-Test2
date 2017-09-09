/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GoToErrorButton.java
 *
 */
package com.gensym.editor.text;



class GoToErrorButton extends TextEditorButton implements ParsingStatusUpdatedListener {
  
  GoToErrorButton( String label ) {
    super(label);
  }

  /** The method that implements ParsingStatusUpdatedListener. 
   * This button should be enabled iff there is an parse error.
   */
  @Override
  public void changeParsingStatus(ParsingStatusUpdatedEvent e) {
    if ( e.statusIsOkQ() )
      setEnabled( false );
    else {
      if ( e.validErrorIndex() )
	setEnabled( true );
      else
	setEnabled( false );
    }
  }

}
