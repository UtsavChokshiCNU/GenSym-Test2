package com.gensym.beaneditor;

import java.awt.Color;

public  class ColorMapRecord{
  private String eventName = "event";
  private Color color = Color.lightGray;
  
  ColorMapRecord(){}
  
  ColorMapRecord(String eventName, Color color){
    this.eventName = eventName;
    this.color = color;
  }
  
  public String getEventName(){
    return eventName;
  }
    
  public void setEventName(String event){
      eventName = event;
  }
  
  public Color getColor(){
    return color;
  }
  
  public void setColor(Color color){
    this.color = color;
  }
}
