/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 UnicodeInserter.java
 *
 * Author: ddm
 * Version: Original, April 1999
 */
package com.gensym.editor.text;

import javax.swing.JTextField;
import javax.swing.AbstractAction;
import javax.swing.text.Document;
import javax.swing.text.PlainDocument;
import javax.swing.text.BadLocationException;
import javax.swing.text.AttributeSet;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import com.gensym.message.Trace;

/** This class provides the capability to interpret a sequence of
 * four hex digits as a Unicode character and insert it at the
 * current cursor position in the editor. It supplies a specialization
 * of a JTextField for entering the characters and an action for
 * directing the session's ui to set up that text field however
 * it likes (presently hard-coded into G2TextEditor). */

class UnicodeInserter  {

  private final boolean debug = false;

  //---- state ---------------

  Session session;
  void setSession(Session s) { session = s; }
  //public Session getSession() { return session; }
  /* The purpose of noting the session is so that we can access the
   * editor from it. We want the editor so we know where to put the
   * character that the user enters. The method that needs it is
   * insertIntoEditor. 
   *   There is either a deep problem in my understanding of the 
   * access rules from methods in inner classes to members in the
   * outer class, or there is a bug, but insertIntoEditor, as a
   * method in the document of the text field, cannot see either
   * this session member or the commented out public accessor to it.
   * (And if you move insertIntoEditor into the scope of the outer
   * class the document can't see it. Six of one half of the other
   * for how to manifest the problem.)
   *   I have gotten around the problem by explicitly passing the
   * session through to the inner classes, first as an argument in 
   * the constructor of the JTextField, and then via a method call
   * on the UnicodDocument. (It can't be in the constructor for
   * the document because it runs in the JTextField's createDefault
   * Model method, which is called before the text field's own
   * constructor is.) This is decidedly ugly. But it does work.
   *  ddm 4/26/99
   */


  //---- Constructor -------------------

  /* Instances of this class are instantiated by calls to Session.getUnicodeInserter().
   * The first need to get something from that call is in TextView.addKeymapBindings,
   * which is part of its constructor, so that is the context that this class will
   * be instantiated in. 
   */
  UnicodeInserter(Session session) {
    this.session = session;
  }




  //---- This action is deployed by the Alt-i KeyStroke in the editor ----

  LaunchUnicoderAction getAction() {
    return new LaunchUnicoderAction();
  }

  /* Might have considered using ui.AbstractCommand rather than
   * swing.AbstractAction, but the type restriction on the keybinding
   * is swing.Action while ui.Command is awt.event.ActionListener.
   * Since swing.Action is an extension of awt.event.ActionListener,
   * the gensym option is spawned off too high to work here. 
   *   For that matter, our Command is actually what I would call
   * a 'CommandSet' since it is a packager for a suite of related
   * commands (e.g. cut, copy, paste), and what is called for as
   * an object to be bound to a keystroke action is one of those
   * individual actions, e.g. 'cut', so the mismatch is actually
   * quite extensive. */
  
  public class LaunchUnicoderAction extends AbstractAction {

    public LaunchUnicoderAction() {
      super("Insert Unicode");
      setEnabled( false );  // ?? is this doing any work now ??
    }

    @Override
    public void actionPerformed(ActionEvent e) {
      if (debug)
	System.out.println("Alt-i keystroke event");
      (session.getFrame()).installUnicodeWidget();
    }
  } // end UnicodeLauncherAction embedded class





  //---- This TextField is where the characters are entered.
  //     The ui for the session has to put it some place. 

  UnicodeEntryField entryField;

  public UnicodeEntryField getEntryField() {
    if ( entryField!= null )
      return entryField;
    else {
      entryField = new UnicodeEntryField(session);
      return entryField;
    }
  }

  class UnicodeEntryField extends JTextField {
    
    Session sess;

    UnicodeEntryField(Session session) {
      sess = session;
      UnicodeDocument d = (UnicodeDocument)getDocument();
      d.setSession(sess);
      setEditable( true );
      setColumns(4);
    }

    @Override
    protected Document createDefaultModel() {
      return new UnicodeDocument();
    }

  } // end UnicodeEntryField inner class




  class UnicodeDocument extends PlainDocument {

    Toolkit toolkit = Toolkit.getDefaultToolkit();

    Session s;
    void setSession(Session session) { s = session; }

    
    /* In principle anyway, the user may be pasting an entire number
     * (or, mistakenly, a sequence of numbers) into the text field,
     * so we need to be somewhat careful and not just assume that
     * we're getting one character at a time as the documentation
     * will instruct people to do. */
    @Override
    public void insertString(final int offset, final String s, final AttributeSet attrs)
    throws BadLocationException {
    String value = s;  
      if (debug)
	System.out.println("Inserting \"" + value + "\"");

      // Truncate if it's too long 
      if ( value.length() > 4 ) { // case of all in one
	toolkit.beep(); 
	toolkit.beep();
	value = value.substring(0, 3);
      }
      else if ( (value.length() > 1) &&
		(getLength() > 0)  ) {  // case of incrementally too much
	if ( (getLength() + value.length()) > 4 ) { // truncate the difference
	  int roomLeft = 4 - getLength();
	  toolkit.beep(); 
	  toolkit.beep();
	  value = value.substring(0, roomLeft);
	}
      }

      // Scan for non-hex characters
      char[] source = value.toCharArray();
      char[] result = new char[source.length];
      int j = 0;
      for (int i = 0; i < result.length; i++) {
	if ( characterIsInRange( source[i] ) )
	  result[j++] = source[i];
	else {
	  toolkit.beep();
	  // trace
	}
      }

      // This will get it into the view
      super.insertString(offset, new String(result, 0, j), attrs);

      if (debug)
	System.out.println("Length is now " + getLength());
	  
      // Check whether we're done now
      if ( getLength() == 4 ) {
	String fullText = getText(0, getLength());
	if (debug)
	  System.out.println("Unicode point is " + fullText);
	insertCorrespondingCharacter(fullText);
	remove(0, 4);
      }
    }

  
    private boolean characterIsInRange(char c) {
      int decimalEquivalent = Character.digit(c, 16);
      if (debug)
	System.out.println("Decimal equivalent of " + c + " is " + decimalEquivalent);
      if ( (decimalEquivalent >= 0) && (decimalEquivalent <= 15) )
	return true;
      else
	return false;
    }


    //---- Converting to char and putting it in the editor ------

    void insertCorrespondingCharacter(String chars) {
      try {
	int code = Integer.parseInt(chars, 16);

	char c = (char)code;
	insertIntoEditor( String.valueOf(c) );

      } catch (NumberFormatException e) {
	Trace.exception(e, "Bad number format: \"" + chars + "\"");
      }
    }


    G2Editor editor;

    void insertIntoEditor(String c) {
      if ( editor == null ) {
	//Session s = getSession();  --This is the call that can't reach
	//     the outer member. Throws NullPointerException.
	editor = s.getEditor();
      }
      if (debug)
	System.out.println("Inserting \"" + c + "\" into the editor at " +
			   editor.getCaretPosition());
      editor.insert(c, editor.getCaretPosition());
    }

  } // end UnicodeDocument inner class

}

