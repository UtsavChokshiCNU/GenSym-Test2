package com.gensym.uilcontrols;

import java.awt.Checkbox;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.modules.uildefs.UilTextToggleButton;
import com.gensym.classes.modules.uildefs.UilIconToggleButton;

public class UILToggleButton extends UILStateButton implements UilClientToggleButton, Serializable{

  static final long serialVersionUID = 1191134289190850066L;

  public UILToggleButton(UilTextToggleButton uilButton, Class staticClass) throws G2AccessException{
    super(uilButton, staticClass);
    uilHelper = new UilClientToggleButtonImpl(uilButton, this, staticClass);
  }

  public UILToggleButton(UilIconToggleButton uilButton, Class staticClass) throws G2AccessException{
    super(uilButton, staticClass);
    uilHelper = new UilClientToggleButtonImpl(uilButton, this, staticClass);
  }

  //properties
  @Override
  public String getTogglelabel(){
    return ((UilClientToggleButton)uilHelper).getTogglelabel();
  }
 
  //API
  @Override
  public void uilUpdateButtonToggleLabel(){
    ((UilClientToggleButton)uilHelper).uilUpdateButtonToggleLabel();
  }
  @Override
  public Symbol uilGetToggleButtonState(){
    return ((UilClientToggleButton)uilHelper).uilGetToggleButtonState();
  }
  @Override
  public void uilSetToggleButtonState(Symbol state) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    ((UilClientToggleButton)uilHelper).uilSetToggleButtonState(state);
  }

}
