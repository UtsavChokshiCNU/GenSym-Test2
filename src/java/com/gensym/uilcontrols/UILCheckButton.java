package com.gensym.uilcontrols;

import java.awt.Checkbox;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilCheckButton;

class UILCheckButton extends UILSelectionButton implements UilClientCheckButton, Serializable{

  static final long serialVersionUID = 4271937372074825149L;

  UILCheckButton(UilCheckButton uilButton, UilClientCheckBox box, Class staticClass) 
       throws G2AccessException{
    super(uilButton, box, staticClass);
    uilHelper = new UilClientCheckButtonImpl(uilButton, this, staticClass);
  }
}
