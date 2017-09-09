package com.gensym.beansruntime;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import com.gensym.message.Trace;

public class PropertyTextField extends TextField 
  implements Resetable
{
  private PropertyEditor editor;
  
  public PropertyTextField(PropertyEditor newEditor)
  {
    super(newEditor.getAsText(), 30);
    editor = newEditor;
    TextFieldChangeAdapter changeAdapter
      = new TextFieldChangeAdapter(this);
    addFocusListener(changeAdapter);
    addActionListener(changeAdapter);
  }

  @Override
  public void repaint()
  {
    setText(editor.getAsText());
  }

  public void applyChanges() {
    String newValue = getText();
    String oldValue = editor.getAsText();
    if (!newValue.equals(oldValue)) {
      try {
	editor.setAsText(newValue);
      } catch (Exception ex) {
	Toolkit.getDefaultToolkit().beep();
	Trace.exception(ex);
      }
    }
  }

  @Override
  public void reset()
  {
    String newText = editor.getAsText ();
    setText(newText);
    select (0, newText.length ());
    requestFocus ();
  }
}
