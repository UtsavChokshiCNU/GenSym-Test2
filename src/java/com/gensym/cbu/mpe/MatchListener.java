package com.gensym.cbu.mpe;

import java.util.EventListener;

public interface MatchListener extends EventListener
{
  public void matchFound(MatchEvent event);
}
