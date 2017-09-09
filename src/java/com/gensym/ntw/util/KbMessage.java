/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbMessage.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Color;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.classes.Message;

class KbMessage implements TableViewMessage{

  private Color foregroundColor=Color.black, bkgColor = Color.white;
  private Message message;
  private String text;
  boolean isValid;

  public KbMessage(Message msg, boolean initText){
    message = msg;
    if (initText){
      try{
	if (msg.isValid()) {
	  text = msg.getText();
	  isValid = true;
	}
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
      }
    }
  }

  @Override
  public Object[] getRowValues(){
    return new Object[]{text};
  }

  @Override
  public void setValueAt(int i, Object aValue){
  }

  @Override
  public Color getBackgroundColor(){
    return bkgColor;
  }

  @Override
  public Color getForegroundColor(){
    return foregroundColor;
  }

  public void setBackgroundColor(Color bc) {
    bkgColor = bc;
  }

  public void setForegroundColor(Color fc) {
    foregroundColor = fc;
  }

  @Override
  public boolean equals(Object o){
    if (o instanceof KbMessage)
      return (((KbMessage)o).message.equals(message));
    return false;
  }

  public Message getMessage(){
    return message;
  }
}

