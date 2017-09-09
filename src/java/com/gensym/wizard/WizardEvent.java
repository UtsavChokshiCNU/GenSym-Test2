package com.gensym.wizard;

import java.awt.Event;

public class WizardEvent extends Event
{

  public WizardEvent(Wizard source, int type, Object argument)
  {
    super(source, type, argument);
  }

}
