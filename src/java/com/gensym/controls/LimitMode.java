package com.gensym.controls;

import java.beans.*;

public class LimitMode implements java.io.Serializable
{
  public static final int NONE      = 0;
  public static final int INCLUSIVE = 1;
  public static final int EXCLUSIVE = 2;
  
  private int mode = 0;

  static final long serialVersionUID = 7303074493375677464L;

  static 
  {
    Class editor = com.gensym.controls.LimitModeEditor.class;
    PropertyEditorManager.registerEditor
      (com.gensym.controls.LimitMode.class,editor);
  }

  public LimitMode(String name)
  {
    if (name.toLowerCase().equals("none"))
      mode = NONE;
    else if (name.toLowerCase().equals("inclusive"))
      mode = INCLUSIVE;
    else if (name.toLowerCase().equals("exclusive"))
      mode = EXCLUSIVE;
    else
      throw new IllegalArgumentException("Unknown Range Mode "+name);
  }

  public LimitMode()
  {
    mode = NONE;
  }

  public boolean isInclusive()
  {
    return mode == INCLUSIVE;
  }

  public boolean isExclusive()
  {
    return mode == EXCLUSIVE;
  }

  @Override
  public String toString()
  {
    switch (mode)
      {
      case NONE:
	return "none";
      case INCLUSIVE:
	return "inclusive";
      case EXCLUSIVE:
	return "exclusive";
      default:
	throw new RuntimeException("Unexpected mode");
      }
  }
  
}
