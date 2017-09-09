package com.gensym.tracebeans;

import java.io.Serializable;

public class TraceElement implements java.io.Serializable {
  
  private String key;
  private String className;
  private int traceLevel;
  
  public TraceElement(String key, 
		      String className,
		      int traceLevel) {
    this.key = key;
    this.className = className;
    this.traceLevel = traceLevel;
  }
  
  public void setKey(String key) {
    this.key = key;
  }
  
  public String getKey() {
    return key;
  }
  
  public void setClassName(String className) {
    this.className = className;
  }
  
  public String getClassName() {
    return className;
  }
  
  public void setTraceLevel(int traceLevel) {
    this.traceLevel = traceLevel;
  }
  
  public int getTraceLevel() {
    return traceLevel;
  }
  
  @Override
  public String toString() {
    return "KEY = " + key + ", CLASS = " + className + ", LEVEL " + traceLevel;  
  }
  
  public boolean equals(TraceElement t) {
    return (traceLevel == t.getTraceLevel() &
	    className.equals(t.getClassName()) &
	    key.equals(t.getKey()));
  }
  
} 
