/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TraceDisplay.java
 *
 */

package com.gensym.tracebeans;


import java.awt.TextArea;

import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.MessageListener;

import java.io.Serializable;

import java.util.Date;

public class TraceDisplay extends TextArea implements MessageListener, Serializable {
  static final long serialVersionUID = -339903425144000899L;
  private boolean includeTimeStamp = true;
  private boolean includeKey = true;
	
  public TraceDisplay() {
    super();
    setEditable(false);
  }

  public void setIncludeKey(boolean includeKey) {
    this.includeKey = includeKey; 
  }

  public boolean getIncludeKey() {
    return includeKey;
  }

  public void setIncludeTimestamp(boolean includeTimeStamp) {
    this.includeTimeStamp = includeTimeStamp; 
  }

  public boolean getIncludeTimestamp() {
    return includeTimeStamp;
  }
		
  @Override
  public void setEditable(boolean editable) {
    if (! editable)
      super.setEditable(editable);
  }

  @Override
  public synchronized void processMessageEvent(MessageEvent event)  
  {
    String key = (includeKey ? event.getMessageKey() + " : " : "");
    if (includeTimeStamp) {
      displayMessage(new Date(System.currentTimeMillis()) + " : "  +
		     key + event.getMessage());
    }
    else  {
      displayMessage(key + event.getMessage());
    }
  }

  private void displayMessage(String message) {
    append(message + "\n");
  }

}


