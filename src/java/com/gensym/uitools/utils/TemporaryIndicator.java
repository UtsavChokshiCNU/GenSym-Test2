package com.gensym.uitools.utils;

import java.awt.Component;
import java.awt.Color;
import com.gensym.message.Trace;

public class TemporaryIndicator extends Thread {
  private Component[] components;
  private Color originalColor;
  private long currentEndTime;
  private boolean somethingToIndicate, running;
  public TemporaryIndicator(Component[] components, Color color) {
    this.components = components;
    originalColor = color;
  }

  public void setRunning(boolean running) {
    this.running = running;
  }
  
  public synchronized void indicate(Color newColor, long time) {
    for (int i=0;i<components.length;i++) {
      components[i].setBackground(newColor);
      components[i].repaint();
    }
    currentEndTime = System.currentTimeMillis() + time;
    somethingToIndicate = true;
    notify();
  }

  private synchronized void turnOffIndicator() {
    somethingToIndicate = false;
    notify();
    for (int j=0; j<components.length; j++){
      components[j].setBackground(originalColor);
      components[j].repaint();
    }
  }
  
  @Override
  public void run() {
    synchronized(this) {
      while(running) {
	try {
	  if (somethingToIndicate) {
	    long timeToWait = currentEndTime - System.currentTimeMillis();
	    if (timeToWait <= 0)
	      turnOffIndicator();
	    else
	      wait(timeToWait);
	  } else
	    wait();
	} catch (InterruptedException ie) {
	  Trace.exception(ie);
	}
      }
    }
  }
}
