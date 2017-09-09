package com.gensym.cbu.odieeventfilterlanguage;

public class TargetIdBlock extends EventFilterBlock
{
  String targetId = "";

  public String getTargetId()
  {
    return targetId;
  }

  public void setTargetId(String targetId)
  {
    this.targetId = targetId;
    if (targetId == "") 
      properlyConfigured = false;
    else 
      properlyConfigured = true;
  }

  @Override
  public String booleanExpression()
  {
    return "(odieEvent.getTargetId().equals(\"" + targetId + "\"))";
  }
}



















