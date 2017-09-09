package com.gensym.uilcontrols;

import java.awt.CheckboxGroup;
import java.lang.reflect.InvocationTargetException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilRadioBox;
import com.gensym.classes.modules.uilroot.UilSelectionButton;
import com.gensym.classes.modules.uillib.UilRadioButton;

public class UILRadioBox extends UILSelectionBox implements UilClientRadioBox{

  static final long serialVersionUID = 8423817281872916146L;

  private CheckboxGroup group = null;

  public UILRadioBox(UilRadioBox uilRadioBox, Class staticClass) throws G2AccessException{
    super(uilRadioBox, staticClass);
    uilHelper = new UilClientRadioBoxImpl(uilRadioBox, this, staticClass);
  }

  @Override
  protected UILSelectionButton createSelectionButton(UilSelectionButton button) throws G2AccessException{
    return new UILRadioButton((UilRadioButton)button, this, (group == null ? group = new CheckboxGroup() : group), staticClass);
  }

  //UilClientRadioBox interface
  //API
  @Override
  public Object uilGetRadioBoxValue(){
    return ((UilClientRadioBox)uilHelper).uilGetRadioBoxValue();
  }
  @Override
  public void uilSetRadioBoxValue(Object value) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    ((UilClientRadioBox)uilHelper).uilSetRadioBoxValue(value);
  }

  Object getCurrentValue(){
    UILRadioButton button = (UILRadioButton)group.getSelectedCheckbox();
    return (button == null ? null : button.getOnValue());
  }

}
