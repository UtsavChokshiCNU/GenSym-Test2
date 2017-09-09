package com.gensym.editor.icon.simulation;

import java.util.Vector;

public class Clock extends Thread {
  public static final int START = 0, PAUSE = 1, RESUME = 2, RESET = 3;
  private int currentTime = 0;
  private Vector timeListeners = new Vector();
  private boolean running = false, started = false;
  private int waitPeriod = 1000;//milliseconds
  private int speedFactor = 10;
      
  public void performAction(int actionKey) {
    switch (actionKey) {
    case START:
      start(); break;
    case PAUSE:
      pause(); break;
    case RESUME:
      res(); break;
    case RESET:
      reset(); break;
    }
  }

  public void setTime(int time) {
    currentTime = time;
  }
  
  @Override
  public synchronized void run() {
    running = true;
    while (true) {
      if (!running) {
	try {
	  wait();
	} catch (InterruptedException ie) {
	}
      }
      try {
	wait(waitPeriod/speedFactor);
      } catch (InterruptedException ie) {
      }	
      currentTime++;
      notifyTimeListeners();
    }
  }
  
  private void notifyTimeListeners() {
    TimeListener[] lstnrs = null;
    synchronized(timeListeners) {
      lstnrs = new TimeListener[timeListeners.size()];
      timeListeners.copyInto(lstnrs);	
    }
    for(int i=0;i<lstnrs.length;i++) 
      lstnrs[i].setTime(currentTime);
  }
  
  public void addTimeListener(TimeListener listener) {
    timeListeners.addElement(listener);
  }

  @Override
  public void start() {
    if (!started) {
      started = true;
      super.start();
    } else
      res();
  }
  
  public void pause() {
    running = false;
  }
  
  public synchronized void res() {
    running = true;
    notify();
  }
  
  public void reset() {
    running = false;    
    currentTime=0;
  }
  
}
