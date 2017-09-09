/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SearchField.java
 *
 */
package com.gensym.editor.text;

import javax.swing.JTextField;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import java.awt.Toolkit;
import java.util.Vector;

class SearchField extends JTextField {

  private boolean debug = false;


  /* Which way are we searching */
  int direction;
  void setDirection(int d) { direction = d; }

  /* Constants to define the two options. */
  static final int FORWARDS = 1;
  static final int BACKWARDS = 2;


  /* The reference point in the editor that any search starts at. */
  int referenceCursor;
  void setReferenceCursor(int c) { referenceCursor = c; }

  /* A record of the position we reached at the end of the last search.
   * At the begining of the next search it is checked against the actual 
   * position of the cursor within the editor as a test that the copy
   * of the text that we're going to search against is still valid.
   */
  int cachedReferenceCursor;

  /* The position at the left end of a successful search */
  int mark;
  int getMark() { return mark; }

  /* The position at the right end of a successful search (cannonically
   * a foward search from left to right */
  int dot;
  int getDot() { return dot; }

  /* Did the last event yield a match against the target text? */
  boolean matched;
  boolean getMatched() { return matched; }

  /* The editor whose text we're searching against. */
  TextSearchTarget editor;

  /* The editor's contents; what we search against.
   * Snapshot taken when the search begins. */
  String target;

  /* What we're searching for. Name is grandiose, but it suggests room
   * for expansion. It is the current contents, getText(), of this field */
  String pattern = "";
  String getPattern() { return pattern; }

  /* The object that is listening to our results */
  SearchAndReplaceManager mgr;

  /* An instance of the Toolkit we can use as the source of a beep */
  Toolkit beeper;



  //------- Constructor ---------

  SearchField(TextSearchTarget editor) {
    super("", 25);  // empty initial text, 25 columns wide
    this.editor = editor;
    target = editor.getText();
    referenceCursor = editor.getReferencePosition();
    cachedReferenceCursor = referenceCursor;
    getDocument().addDocumentListener( new MyDocumentListener() );
    direction = FORWARDS;
    beeper = Toolkit.getDefaultToolkit();
    if (debug)
      System.out.println("The editor is " + editor +
			 "\nIts contents are \"" + target + "\"" +
			 "\nand it is at cursor position " + referenceCursor);
  }

  
  //------- TextListener ----------

  class MyDocumentListener implements DocumentListener {

    @Override
    public void insertUpdate(DocumentEvent e) {
      if (debug)
	System.out.println("insertUpdate event");
      pattern = SearchField.this.getText();
      search();
    }

    @Override
    public void removeUpdate(DocumentEvent e) {
      if (debug)
	System.out.println("removeUpdate event");
      pattern = SearchField.this.getText();
      search();
    }

    @Override
    public void changedUpdate(DocumentEvent e) {
      if (debug)
	System.out.println("Incremental search: got a changedUpdate");
      pattern = SearchField.this.getText();
      search();
    }
  }  // end of the inner class






  //---------- the Search operation proper ------------

  void search() {
    /* Check for the editor having moved out from under us.
     * If it has, reset the text that we're searching and reset the
     * position we're searching from to the current text and
     * cursor position, ignoring any relative reference position
     * we got when called from the next or previous buttons. */
    if ((cachedReferenceCursor != editor.getReferencePosition())
	|| //(target.length() != editor.getText().length())
	( ! target.equals(editor.getText()) )) {
      target = editor.getText();
      referenceCursor = editor.getReferencePosition();
    }
    switch ( direction ) {
    case FORWARDS:
      if (debug)
	System.out.println("Searching forwards from " + referenceCursor +
			   "\n  for \"" + pattern + "\"" );
      mark = target.indexOf(pattern, referenceCursor);
      break;
    case BACKWARDS:
      if (debug)
	System.out.println("Searching backwards from " + referenceCursor +
			   "\n  for \"" + pattern + "\"" );
      mark = searchBackwards(pattern, referenceCursor);
      break;
    default:
    }
    matched = mark != -1 ;
	
    if ( matched ) {
      dot = mark + pattern.length();	
      editor.showRegion(mark, dot);
      fireServiceStateEvent ( new ServiceStateEvent( this, ServiceStateEvent.Replace, true));
      if (debug)
	System.out.println("Found a match between " + mark + " and " + dot);
    }
    else {
      if (debug)
	System.out.println("no match");
      beeper.beep();
      fireServiceStateEvent ( new ServiceStateEvent( this, ServiceStateEvent.Replace, false));
    }

    cachedReferenceCursor = editor.getReferencePosition();
  }


  /* You might think that this is just string.lastIndexOf(pattern, referenceCursor),
   * and you'd be right if 'pattern' was an integer (naming a unicode character),
   * but if it's a string, as it is in our case, that method means 'find the
   * last instance of pattern in the entire string, starting at referenceCursor,
   * which is completely the wrong thing. 
   *   This implementation is wasteful because each call is going to make a
   * throw-away substring, but search operations are at human speeds and are
   * relatively infrequent (?), so I'm going for simplicity in this first
   * implementation and will wait for a specific reason to speed it up. 
   */
  int searchBackwards(String pattern, int referenceCursor) {
    String r = target.substring(0, referenceCursor);
    return r.lastIndexOf(pattern);
  }

  //-------- Support Methods for ServiceStateEvents to notify listeners
  //          about the state of the search: true = there's a match  ---------

  Vector listeners = new Vector();

  public void addServiceStateListener (ServiceStateListener listener) {
    listeners.addElement(listener);
  }

  public void removeServiceStateListener (ServiceStateListener listener) {
    listeners.removeElement(listener);
  }

  public void fireServiceStateEvent (ServiceStateEvent event) {
    int size = listeners.size();
    for (int i=0; i < size; i++) {
      ((ServiceStateListener)(listeners.elementAt(i))).serviceStateChanged(event);
    }
  }





}  // end of class
