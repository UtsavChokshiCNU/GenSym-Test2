package com.gensym.uitools.utils;

import java.awt.event.ActionEvent;

public class StepEvent extends ActionEvent
{

  public StepEvent(JWizard source, int type, String command)
  {
    super(source, type, command);
  }

}
