/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TraceTool.java
 *
 */

package com.gensym.tracebeans;


import java.io.Serializable;

public class TraceTool extends TraceDisplay {
	
  private TraceFilter filter;

  public TraceTool() {
    super();
    filter = new TraceFilter();
    filter.addMessageListener(this);
  }
   
  public TraceElementVector getTraces() 	{  
    return filter.getTraces();
  }

  public void setTraces(TraceElementVector traces)	{
    filter.setTraces(traces);   
  }


  /* Most properties are simply a wrapper around the properties
   * in TraceFilter 
   */

  public boolean getIsRunning() {
    return filter.getIsRunning();
	
  }

  public void setIsRunning(boolean isRunning) {
    filter.setIsRunning(isRunning);
  }

	
  public boolean getTraceOn() {
    return filter.getTraceOn();
  }

  public void setTraceOn(boolean traceOn ) {
    filter.setTraceOn(traceOn);
  }


  /* NB. includes are defined in both this and the filter
     because of the distinction between the format of the
     file produced and the format of the display. I considered
     adding a separate property to control the file format but
     decided it would just be an extra confusion.
     */

  @Override
  public boolean getIncludeKey() {
    boolean includeKey = filter.getIncludeKey();
    super.setIncludeKey(includeKey);
    return includeKey; 
  }

  @Override
  public void setIncludeKey(boolean includeKey) {
    super.setIncludeKey(includeKey);
    filter.setIncludeKey(includeKey);
  }

  @Override
  public void setIncludeTimestamp(boolean includeTimestamp) {
    super.setIncludeTimestamp(includeTimestamp);
    filter.setIncludeTimestamp(includeTimestamp);
  }

  @Override
  public boolean getIncludeTimestamp() {
    boolean includeTimestamp = filter.getIncludeTimestamp();
    super.setIncludeTimestamp(includeTimestamp);
    return includeTimestamp; 
  }


  public void setLogToFile(boolean logToFile) {
    filter.setLogToFile(logToFile);
  }

  public boolean getLogToFile() {
    return filter.getLogToFile();
  }

  public void setLogFile(String logFile) {
    filter.setLogFile(logFile);
  }

  public String getLogFile() {
    return filter.getLogFile();
  }

  public void setLogToStdout(boolean logToStdout) {
    filter.setLogToStdout(logToStdout);
  }

  public boolean getLogToStdout() {
    return filter.getLogToStdout();
  }

  public void setLogAppend(boolean logAppend) {
    filter.setLogAppend(logAppend);
  }

  public boolean getLogAppend() {
    return filter.getLogAppend();
  }

  public synchronized boolean startRunning() {
    return filter.startRunning();
  }

  public synchronized void stopRunning () {
    filter.stopRunning();
  }
}
