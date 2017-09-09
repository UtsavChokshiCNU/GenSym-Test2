package com.gensym.beansruntime;

import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

class TextFieldChangeAdapter implements FocusListener, ActionListener{

  PropertyTextField textField;

  TextFieldChangeAdapter(PropertyTextField textField) {
    this.textField = textField;
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    textField.applyChanges();
  }

  @Override
  public void focusGained(FocusEvent e) {
  }

  @Override
  public void focusLost(FocusEvent e) {
    if (!e.isTemporary())
      textField.applyChanges();
  }
}
