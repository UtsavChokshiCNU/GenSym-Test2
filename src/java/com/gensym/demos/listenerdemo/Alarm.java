package com.gensym.demos.listenerdemo;

import java.applet.Applet;

public class Alarm implements Runnable{
  private Applet applet;

  public Alarm(Applet applet){
    this.applet = applet;
  }

  @Override
  public void run(){
    while (true){
      applet.play(applet.getCodeBase(), "beep.au");
      try{
	Thread.sleep(1000);
      }catch (InterruptedException e){}
    }
  }
}
