
package com.gensym.editor;

import java.awt.*;
import java.awt.event.*;

public class TextEditor extends Frame {

  public TextEditor (String title) {
    super (title);
    TextArea ta;
    setLayout (new BorderLayout ());
    add (ta = new TextArea (), "Center");
    ta.addTextListener (new MyTextListener ());
    ta.addFocusListener (new MyFocusListener ());
    ta.addKeyListener (new MyKeyListener ());
  }

  public static void main (String[] args) {
    TextEditor te = new TextEditor ("Demo");
    te.setSize (400, 300);
    te.setVisible (true);
  }
}

class MyTextListener implements TextListener {

  private java.io.PrintStream o = System.out;
  @Override
  public void textValueChanged (TextEvent te) {
    o.println ("Got " + te);
    TextArea ta = (TextArea) te.getSource ();
    String currentTxt = ta.getText ();
    o.println ("Current Text = " + currentTxt);
    int cursorBegin = ta.getSelectionStart ();
    int cursorEnd   = ta.getSelectionEnd ();
    if (cursorBegin == cursorEnd)
      o.println ("Cursor is at : " + cursorBegin);
    else
      o.println ("Text Selection : [" + cursorBegin + ", " + cursorEnd + "]");
  }
}

class MyFocusListener implements FocusListener {

  private java.io.PrintStream o = System.out;
  @Override
  public void focusGained(FocusEvent e) {
    o.println ("Foucs Event : " + e);
  }
  @Override
  public void focusLost (FocusEvent e) {
    o.println ("Foucs Event : " + e);
  }
}

class MyKeyListener implements KeyListener {

  private java.io.PrintStream o = System.out;
  @Override
  public void keyTyped(KeyEvent e) {
    o.println ("Key Typed : " + e);
  }
  @Override
  public void keyPressed(KeyEvent e) {
    o.println ("Key Pressed : " + e);
  }
  @Override
  public void keyReleased(KeyEvent e) {
    o.println ("Key Released : " + e);
  }
}
