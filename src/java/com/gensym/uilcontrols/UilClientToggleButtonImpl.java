package com.gensym.uilcontrols;

import java.awt.Checkbox;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uildefs.UilIconToggleButton;
import com.gensym.classes.modules.uildefs.UilTextToggleButton;

class UilClientToggleButtonImpl extends UilClientStateButtonImpl implements UilClientToggleButton, Serializable{

  static final long serialVersionUID = 1560003350629139191L;

  private String toggleLabel;
  
  UilClientToggleButtonImpl(UilIconToggleButton uilButton, UILToggleButton component,
			    Class staticClass) throws G2AccessException{
    super(uilButton, component, staticClass);
    toggleLabel = (String)uilButton.getTogglelabel();
    init();
  }

  UilClientToggleButtonImpl(UilTextToggleButton uilButton, UILToggleButton component, Class staticClass) 
       throws G2AccessException{
    super(uilButton, component, staticClass);
    toggleLabel = (String)uilButton.getTogglelabel();
    init();
  }

  private void init(){
    Checkbox checkbox = (Checkbox)getComponent();
    if (getToggleState().equals(ON_)) checkbox.setLabel(toggleLabel);
    else checkbox.setLabel(getUilLabel());
  }

  @Override
  protected void setButtonStateOn(boolean callback) throws G2AccessException, G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    //System.out.println("UilClientToggleButtonImpl.setButtonStateOn");
    ((Checkbox)getComponent()).setLabel(toggleLabel);
    super.setButtonStateOn(callback);
  }

  @Override
  protected void setButtonStateOff(boolean callback) throws G2AccessException, G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    //System.out.println("UilClientToggleButtonImpl.setButtonStateOff");
    ((Checkbox)getComponent()).setLabel(getUilLabel());
    super.setButtonStateOff(callback);
  }

  //properties
  @Override
  public String getTogglelabel(){
    return toggleLabel;
  }

  //API
  @Override
  public void uilUpdateButtonToggleLabel(){
    //do nothing
  }

  @Override
  public Symbol uilGetToggleButtonState() {
    return getToggleState();
  }

  @Override
  public void uilSetToggleButtonState(Symbol state) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    Symbol toggleState = getToggleState();
    if (state.equals(ON_) && toggleState.equals(OFF_))
      setButtonStateOn(true);
    else if (state.equals(OFF_) && toggleState.equals(ON_))
      setButtonStateOff(true);
  }
}









