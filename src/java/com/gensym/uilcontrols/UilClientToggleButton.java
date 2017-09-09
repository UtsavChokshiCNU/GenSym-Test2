package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;

public interface UilClientToggleButton extends UilClientStateButton{

  //properties
  public String getTogglelabel();

  //API
  public void uilUpdateButtonToggleLabel();
  public Symbol uilGetToggleButtonState();
  public void uilSetToggleButtonState(Symbol state) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;

}
