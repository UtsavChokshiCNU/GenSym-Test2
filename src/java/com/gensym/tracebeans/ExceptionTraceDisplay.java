/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *   ExceptionTraceDisplay.java
 *
 */

package com.gensym.tracebeans;

import java.awt.*;
import java.awt.event.*;
import java.util.Date;

import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.MessageListener;
import com.gensym.message.Trace;

public class ExceptionTraceDisplay extends Container implements MessageListener {

  private static final String exceptionKey = "com.gensym.trace.exception";
  private static final String internalKey = "com.gensym.trace.force";

  TextArea displayArea;
  TraceControlPanel controlPanel;
  private boolean isTracing, initialTraceState;
  private boolean includeTimeStamp = false;
  private boolean includeKey = false;

  public ExceptionTraceDisplay () {
    setLayout (new BorderLayout ());
    add (displayArea = new TextArea (), BorderLayout.CENTER);
    add (controlPanel = new TraceControlPanel (this), BorderLayout.SOUTH);
    displayArea.setEditable (false);
  }

  public boolean isTracingInitiallyOn () {
    return initialTraceState;
  }

  public void setTracingInitiallyOn (boolean newTraceState) {
    initialTraceState = newTraceState;
  }

  boolean isTracingOn () {
    return isTracing;
  }

  void setTracingOn (boolean newTraceState) {
    if (newTraceState == isTracing)
      return;
    isTracing = newTraceState;
    if (newTraceState) {
      Trace.setExceptionTraceOn (true);
      Message.addMessageListener (this, exceptionKey, java.lang.Object.class, 0);
      Trace.setTraceOn (true);
      Message.addMessageListener (this, internalKey, java.lang.Object.class, 0);
    } else {
      Trace.setExceptionTraceOn (false);
      Message.removeMessageListener (this, exceptionKey);
      Trace.setTraceOn (false);
      Message.removeMessageListener (this, internalKey);
    }
  }

  @Override
  public synchronized void processMessageEvent(MessageEvent event) {
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
    displayArea.append(message + "\n");
  }

  private void readObject (java.io.ObjectInputStream stream) throws java.io.IOException, ClassNotFoundException {
    stream.defaultReadObject();
    if (initialTraceState) {
      controlPanel.onOffSwitch.setState (true);
      setTracingOn (true);
    } else
      setTracingOn (false);
  }

}
