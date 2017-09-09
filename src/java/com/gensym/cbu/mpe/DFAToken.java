package com.gensym.cbu.mpe;

public class DFAToken
{
  String name;
  boolean isStop;

  DFAToken(String name)
  {
    this.name = name;
  }

  public DFAToken()
  {

  }

  public String getName()
  {
    return name;
  }

  public void setName(String name)
  {
    this.name = name;
  }

  public boolean isStop()
  {
    return isStop;
  }

  public void setStop(boolean isStop)
  {
    this.isStop = isStop;
  }
}
