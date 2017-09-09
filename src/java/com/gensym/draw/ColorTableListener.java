package com.gensym.draw;

import java.util.EventListener;

public interface ColorTableListener extends EventListener
{
  void colorTableChanged(ColorTableEvent e);
}
