/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TraceFilter.java
 *
 */

package com.gensym.tracebeans;

import java.awt.TextArea;

import com.gensym.message.Trace;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.MessageListener;

import java.io.Serializable;
import java.io.ObjectInputStream;
import java.io.IOException;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;

import java.util.Date;
import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Vector;

import java.beans.*;
import java.awt.*;
import java.awt.event.*;

public class TraceFilter  implements MessageListener, Serializable {
  static final long serialVersionUID = 7324921315559415737L;

  protected TraceElementVector traces = new TraceElementVector();
  protected Hashtable cachedTraces = new Hashtable();

  private boolean isRunning = false;
  private boolean traceOn = Trace.getTraceOn();
  private boolean includeTimeStamp = true;
  private boolean includeKey = true;
	
  private boolean logToFile = false;
  private String logFile;	
  private boolean logAppend = true;
  private boolean logToStdout = false;
  private Hashtable listeners = new Hashtable();

  private transient FileOutputStream fout;
  private transient PrintWriter print;
	
  
  public TraceFilter() {
    super();
  }
		
  public void setTraces(TraceElementVector traces) 	{  
    if (isRunning)
      swapTracesWhileRunning(traces);
    this.traces = traces;
  }

  public TraceElementVector getTraces() {
    return traces;
  }

  public boolean getIsRunning() {
    return isRunning;
  }

  public void setIsRunning(boolean isRunning) {
    if (isRunning & (!this.isRunning))
      startRunning();
    if (! isRunning & this.isRunning) 
      stopRunning();
  }

  public void setTraceOn(boolean traceOn ) {
    Trace.setTraceOn(traceOn);
    this.traceOn = Trace.getTraceOn();
  }

  public boolean getTraceOn() {
    return Trace.getTraceOn();
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

  public void setLogToFile(boolean logToFile) {
    boolean oldLogToFile = this.logToFile;
    this.logToFile = logToFile;	
    if (logToFile & (logFile != null)  & isRunning 
	& (! oldLogToFile))	
      swapFileWhileRunning(logFile);
    if (! logToFile & oldLogToFile) 
      closeFile();
  }

  public boolean getLogToFile() {
    return logToFile;
  }

  public void setLogFile(String logFile) {
    String oldLogFile =  this.logFile;
    this.logFile = logFile;
    if (logToFile & (logFile != null) & isRunning
	& (oldLogFile == null || (! oldLogFile.equals(logFile))))
      swapFileWhileRunning(logFile);
    if (logFile == null & oldLogFile != null)
      closeFile();
  }

  public String getLogFile() {
    return logFile;
  }

  public void setLogToStdout(boolean logToStdout) {
    this.logToStdout = logToStdout; 
  }

  public boolean getLogToStdout() {
    return logToStdout;
  }

  public void setLogAppend(boolean logAppend) {
    boolean oldLogAppend = this.logAppend;
    this.logAppend = logAppend;
    if (isRunning & logToFile & (logFile != null)
	& (logAppend != oldLogAppend)) {
      closeFile();
      swapFileWhileRunning(logFile);
    }
  }

  public boolean getLogAppend() {
    return logAppend;
  }

  public synchronized boolean startRunning() {
    if (traces.size() == 0)
      return false;
    isRunning = true;
    swapTracesWhileRunning(traces);
    if (logToFile & (logFile != null) & (fout == null))
      swapFileWhileRunning(logFile);
    return true;
  }

  public synchronized void stopRunning () {
    swapTracesWhileRunning(new TraceElementVector());
    isRunning = false;
  }

  @Override
  public synchronized void processMessageEvent(MessageEvent event)  
  {
    Enumeration e = listeners.keys();

    while( e.hasMoreElements()) {
      MessageListener l  = (MessageListener) e.nextElement();
      l.processMessageEvent(event);	
    }
		
    String key = (includeKey ? event.getMessageKey() + " : " : "");
    if (includeTimeStamp) {
      displayMessage(new Date(System.currentTimeMillis()) + " : "  +
		     key + event.getMessage());
    }
    else  {
      displayMessage(key + event.getMessage());
    }
  }

  public synchronized void addMessageListener(MessageListener l) 
  {	
    if (! listeners.containsKey(l))
      listeners.put(l,l);	
  }

  public synchronized void removeMessageListener(MessageListener l) 
  {
    if (listeners.containsKey(l))
      listeners.remove(l);
  }


  private void displayMessage(String message) {	

    if (logToFile & (print != null)) {
      print.println(message);
      print.flush();
    }
    if (logToStdout)
      System.out.println(message);
  }

			
  private synchronized void swapTracesWhileRunning(TraceElementVector traces) {
    int size = traces.size();
    TraceElement t;
      
    if (isRunning) {                         
      Enumeration keys = cachedTraces.keys();
      while(keys.hasMoreElements()) {
	t = (TraceElement) keys.nextElement();
	Message.removeMessageListener(this, t.getKey());                
      }
      cachedTraces = new Hashtable();
    }

    for (int i =0; i < size; i++) {
      t = (TraceElement) traces.elementAt(i);
      if (isRunning & (! cachedTraces.containsKey(t))) {
	try {
	  String className = t.getClassName();
	  String key = t.getKey();
	  Class traceclass;
                    
	  if (key == null || key.equals(""))
	    continue;
                    
	  if (className == null || className.equals("")) {
	    traceclass = java.lang.Object.class;
	  }
	  else  traceclass = Class.forName(t.getClassName());                    
                  
	  Message.addMessageListener(this, key, traceclass, t.getTraceLevel());
	  cachedTraces.put(t,t);
	}
	catch (Exception e) {

	}
      }                   
    }
  }	


 
  private synchronized void swapFileWhileRunning(String fileName) {
    try {
      fout = new FileOutputStream(fileName,logAppend);
      print = new PrintWriter(fout);
      if (logAppend)
	displayMessage("< Logfile opened for append = " + fileName + " >");
      else displayMessage("< Logfile opened = " + fileName + " >");
    }
    catch(IOException e) {
      displayMessage("< Logfile could not be opened: " + fileName + " >");
      print = null;
      return;
    }	
  }

  private synchronized void closeFile() {
    if (fout != null)  {
      try {
	fout.close();
      }
      catch (IOException e) {
      }
      fout = null;	
    }
    print = null;
  }

  private void readObject(ObjectInputStream in) throws IOException  {
    try {
      in.defaultReadObject();
      if (isRunning)
	startRunning();
      // If it was previously running with certain trace levels
      // then make sure that these are restored globally
      if (traceOn)
	setTraceOn(true);
    }
    catch (Exception e) {
      isRunning = false;
    }
  }
}




