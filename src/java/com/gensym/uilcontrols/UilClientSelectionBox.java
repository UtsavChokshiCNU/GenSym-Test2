package com.gensym.uilcontrols;

import com.gensym.util.Symbol;

public interface UilClientSelectionBox extends UilClientGrobj{

  public static final Symbol VERTICAL_ = Symbol.intern("VERTICAL");
  public static final Symbol HORIZONTAL_ = Symbol.intern("HORIZONTAL");

  //properties
  public Symbol getUilButtonOrientation();
  public Symbol getUilState();
  public String getLabel();
  public boolean getUilUpdateValue();
  public int getUilBorderXOffset();
  public int getUilBorderYOffset();
  public int getUilLabelXOffset();
  public int getUilLabelYOffset();

  //API
  public UilClientStateButton[] getMembers();
}
