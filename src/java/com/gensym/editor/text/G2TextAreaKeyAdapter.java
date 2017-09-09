package com.gensym.editor.text;

import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import javax.swing.JTextArea;
import com.gensym.message.Trace;

/**
 * An adapter implementing the typical listener interfaces required to get
 * "G2 like" key-stroke accellerators and prompt insertion.
 */
public class G2TextAreaKeyAdapter
implements KeyListener, PromptsTarget, PromptSelectionListener
{
  private JTextArea textArea;
  private ParserController controller;
  public G2TextAreaKeyAdapter(JTextArea textArea, ParserController controller) {
    this.textArea = textArea;
    this.controller = controller;
  }
  @Override
  public String getLeftPromptContext (int length) {
    int here = textArea.getCaretPosition();
    if ( here <= length )
      return textArea.getText().substring(0, here);
    else {
      return textArea.getText().substring(here - length, here);
    }      
  }
  @Override
  public void promptSelected(String prompt) {
    insertPrompt(prompt, false);
  }
  @Override
  public String getRightPromptContext (int length) {
    String text = textArea.getText();
    int here = textArea.getCaretPosition();
    int textLength = text.length();
    int lengthRemaining = textLength - here;
    if ( lengthRemaining <= length )
      return text.substring(here);
    else 
      return text.substring(here, here + length);      
  }
  @Override
  public void insertPromptStringAtCursor (String s) {
    textArea.insert(s, textArea.getCaretPosition());
  }
  @Override
  public void moveCursor(int delta) {
    textArea.setCaretPosition(textArea.getCaretPosition()+delta);
  }
  public void insertPrompt(String prompt, boolean removeLastChar) {
    PromptManager.insertPrompt(prompt, this);
    int pos = textArea.getCaretPosition();
    if (removeLastChar) {//HACK
      try {
	textArea.getDocument().remove(pos-1, 1);
      } catch (javax.swing.text.BadLocationException ble) {
	Trace.exception(ble);	    
      }
    }
  }    
  @Override
  public void keyReleased(java.awt.event.KeyEvent e) {
  char key = e.getKeyChar();    
    switch (e.getKeyCode()) {    
    case KeyEvent.VK_ENTER:
    case KeyEvent.VK_ACCEPT:
      if (e.isControlDown()) {
	e.consume();
	controller.accept();
      }
      break;
    }    
  }
  
  @Override
  public void keyTyped(KeyEvent e) {
  }
  
  @Override
  public void keyPressed(KeyEvent e) {
    char key = e.getKeyChar();
    switch (e.getKeyCode()) {
    case KeyEvent.VK_CANCEL:
    case KeyEvent.VK_ESCAPE:
      e.consume();
      controller.escape();
      break;
    case KeyEvent.VK_SPACE:
      if (e.isControlDown()) {
	e.consume();	  
	String token = null;
	Prompter prompter = EditContext.getContext().getPrompter();
	if (prompter != null) {
	  if (e.isShiftDown())
	    token = prompter.getLastItem();
	  else
	    token = prompter.getFirstItem();
	  if (token != null)
	    insertPrompt(token, true);	  		  
	}
      }
      break;
    case KeyEvent.VK_X:
      if (e.isControlDown()) {
	try {
	  if (textArea.getSelectedText() != null) 
	    textArea.getDocument().remove(textArea.getSelectionStart(), textArea.getSelectionEnd());
	  else
	    textArea.getDocument().remove(0, textArea.getCaretPosition());
	} catch (javax.swing.text.BadLocationException ble) {
	  Trace.exception(ble);
	}
      }
      break;
    }
  }    
}
