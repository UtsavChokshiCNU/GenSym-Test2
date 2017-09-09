package com.gensym.cbu.odie;

import java.util.EventListener;

public interface OslConnectionListener extends EventListener
{
  public void passEvent(OslConnectionEvent event);
}
