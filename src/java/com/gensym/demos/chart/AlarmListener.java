package com.gensym.demos.chart;

public interface AlarmListener extends java.util.EventListener
{
  public void outOfControlPointReceived(AlarmEvent e);
}
