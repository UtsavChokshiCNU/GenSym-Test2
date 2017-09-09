package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.jgi.G2AccessException;

public interface UilClientRadioBox extends UilClientSelectionBox{

  //Properties
  //public Object getRadioBoxCurrentValue();
  //public void setRadioBoxCurrentValue(Object value);

  //API
  public Object uilGetRadioBoxValue();
  public void uilSetRadioBoxValue(Object value) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
}


