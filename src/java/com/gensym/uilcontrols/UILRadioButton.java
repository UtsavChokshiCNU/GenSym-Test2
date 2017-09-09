package com.gensym.uilcontrols;

import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilRadioButton;

class UILRadioButton extends UILSelectionButton implements UilClientRadioButton, Serializable{

  static final long serialVersionUID = 5837830208867308333L;

  UILRadioButton(UilRadioButton uilButton, UILRadioBox box, CheckboxGroup group,
		 Class staticClass) throws G2AccessException{
    super(uilButton, box, group, staticClass);
    uilHelper = new UilClientRadioButtonImpl(uilButton, this, staticClass);
  }

}
