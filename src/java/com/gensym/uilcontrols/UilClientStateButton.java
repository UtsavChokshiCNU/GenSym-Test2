package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;

public interface UilClientStateButton extends UilClientButton{

  public static final Symbol ON_ = Symbol.intern("ON");
  public static final Symbol OFF_ = Symbol.intern("OFF");

  //properties
  public String getUilLabel();
  public Symbol getToggleState();
  public Object getOnValue();
  public Object getOffValue();
  public boolean getUilUpdateValue();

  public void setUilLabel(String label);
  public void setToggleState(Symbol state);

  //API
  public void uilToggleButton(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;

  //misc
  public void uilToggleButtonNoCallback();
}
