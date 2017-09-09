/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Timer.java
 *
 */
package com.gensym.editor.text;

import java.lang.Thread;
import java.util.Locale;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

public class Timer extends Thread {

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.editor.text",
			   Timer.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.editor.text.TraceMessages", Locale.getDefault());

  private static final int DEF_TRACE_LEVEL     = 5;
    
  private static final int DEFAULT_TIMEOUT = 200; //500;  // in milliseconds

  private transient volatile boolean timedOut = true;

  private transient volatile TextView editor;  /* what we're timing */
  void setEditor(TextView e) { editor = e; }
  TextView getEditor() { return editor; }


  public Timer() {
    super ("Prompting Timer");
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "createTimer", this);
    setDaemon (true);		// Don't let this hold up the VM
    start ();
  }

  public synchronized void resetTimeout(TextView editor) {
    timedOut = false;
    notifyAll();
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "resetTimer", this, editor);
    this.editor = editor;
  }


  private int timeOut = DEFAULT_TIMEOUT;
  private int timerDelta = timeOut;

  int getTimerDelta() { return timeOut; }
  void setTimerDelta(int d) { timeOut = d; }

  @Override
  public synchronized void run() {
    try {
      if (editor == null)
	timerDelta = 0;
      while (true) {
	timedOut = true;
	wait (timerDelta);
	timerDelta = timeOut;
	if (timedOut) {
	  Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "timerExpired", this);
	  if ( editor.getPendingTextChange() ) {
	    editor.sendTextChangesToParser();
	    editor.setPendingTextChange(false);
	  } 
	  timerDelta = 0;
	}
	timedOut = true;
      }
    } catch (java.lang.InterruptedException e) {
      e.printStackTrace();
    }
  }

}
	

