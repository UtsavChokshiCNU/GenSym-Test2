package com.gensym.beaneditor;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

class Timer implements Runnable{

  private static final String ACTION_COMMAND = "TimeUp";

  private int delay;
  private ActionListener listener;

  Timer(int delay, ActionListener listener){
    this.delay = delay;
    this.listener = listener;
  }

  @Override
  public void run(){
    try{
      Thread.sleep(delay);
    }catch (InterruptedException e){
      System.out.println("interrupted");
    }
    listener.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, ACTION_COMMAND));
  }
  
}
