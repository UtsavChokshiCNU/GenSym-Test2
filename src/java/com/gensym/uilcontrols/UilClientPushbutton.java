package com.gensym.uilcontrols;

import com.gensym.util.Symbol;
import com.gensym.classes.SymbolArray;

public interface UilClientPushbutton extends UilClientButton{

  //properties
  public String getUilLabel();
  public boolean getUilDefaultedButton();
  public boolean getUilCancelButton();
  public boolean getUilUpdateButton();
  public boolean getUilReleaseButtonAfterSelection();
  public boolean getUilUpdateValue();
  public UilCallback[] getActions();
  //public SymbolArray getUilActionDescriptionArray();

  public void setUilLabel(String label);
}
