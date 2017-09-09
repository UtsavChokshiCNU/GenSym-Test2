/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2TextField.java
 *
 */

package com.gensym.jcontrols;

import javax.swing.text.Document;
import javax.swing.event.DocumentListener;
import javax.swing.event.DocumentEvent;
import java.io.Serializable;

class G2DocumentAdapter implements Serializable, DocumentListener {

  @Override
  public void insertUpdate(DocumentEvent e){
    textValueChanged();
  }

  @Override
  public void removeUpdate(DocumentEvent e){
    textValueChanged();
  }

  @Override
  public void changedUpdate(DocumentEvent e){
  }

  private transient G2TextField g2TextField;

  G2TextField getG2TextField(){
      return g2TextField;
  }

  void setG2TextField(G2TextField g2TextField){
    this.g2TextField = g2TextField;
  }

  private void textValueChanged() {
    if (g2TextField != null) {
      g2TextField.textValueChanged();
    }
  }
}
