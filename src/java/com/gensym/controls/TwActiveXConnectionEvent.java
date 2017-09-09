package com.gensym.controls;

import com.gensym.ntw.TwConnectionEvent;

public class TwActiveXConnectionEvent extends java.util.EventObject{
  private com.gensym.ntw.TwConnectionEvent wrapped;
  public TwActiveXConnectionEvent(Object source, TwConnectionEvent wrapped){
    super(source);
    this.wrapped = wrapped;
  }

  public com.gensym.util.Symbol getUserMode(){
    com.gensym.util.Symbol returnVar = null;
    returnVar = wrapped.getUserMode();
    return returnVar;
  }

  public int getId(){
    int returnVar = (int)0;
    returnVar = wrapped.getId();
    return returnVar;
  }
}
