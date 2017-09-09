package com.gensym.g2scriptruntime;

public interface RegistrationListener
{
  public void registerObject(RegistrationEvent e);

  public void deregisterObject(RegistrationEvent e);

}
