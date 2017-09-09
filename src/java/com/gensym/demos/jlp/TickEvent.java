package com.gensym.demos.jlp;

public class TickEvent extends java.util.EventObject {

  private long tick = 0;

  public TickEvent(Object source, long tick) {
    super(source);
    this.tick = tick;
  }

  public long getTick() {
    return tick;
  }

  public int getTickAsInt() {
    return (int)tick;
  }
}
