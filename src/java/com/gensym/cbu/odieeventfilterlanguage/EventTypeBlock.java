package com.gensym.cbu.odieeventfilterlanguage;

public class EventTypeBlock extends EventFilterBlock
{
  String eventType = "";

  public String getEventType()
  {
    return eventType;
  }

  public void setEventType(String eventType)
  {
    this.eventType = eventType;
  }

  @Override
  public String booleanExpression()
  {
    return "(odieEvent.getEventType() == " + eventType + ")";
  }

  public boolean properlyConfigured()
  {
    if (eventType == "") 
      return false;
    else
      return true;
  }

}









