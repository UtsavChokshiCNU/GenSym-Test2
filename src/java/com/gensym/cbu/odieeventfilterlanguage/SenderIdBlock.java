package com.gensym.cbu.odieeventfilterlanguage;

public class SenderIdBlock extends EventFilterBlock
{
  String senderId = "";

  public String getSenderId()
  {
    return senderId;
  }

  public void setSenderId(String senderId)
  {
    this.senderId = senderId;   
    if (senderId == "") 
      properlyConfigured = false;
    else 
      properlyConfigured = true;
  }

  @Override
  public String booleanExpression()
  {
    return "(odieEvent.getSenderId().equals(\"" + senderId + "\"))";
  }
}



















