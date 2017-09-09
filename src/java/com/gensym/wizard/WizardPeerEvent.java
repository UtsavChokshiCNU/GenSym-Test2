package com.gensym.wizard;

import java.awt.Event;

public class WizardPeerEvent extends Event
{

  public WizardPeerEvent(WizardPeer source, int type, Object argument)
  {
    super(source, type, argument);
  }

}
