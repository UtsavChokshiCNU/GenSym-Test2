package com.gensym.uitools.utils;

public interface StepListener
{
  public void stepForward(StepEvent e);
  public void stepBack(StepEvent e);
  public void stepFinish(StepEvent e);
  public void stepCancel(StepEvent e);
   
}
