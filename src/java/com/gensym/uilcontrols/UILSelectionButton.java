package com.gensym.uilcontrols;

import java.awt.CheckboxGroup;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.modules.uilroot.UilSelectionButton;

public class UILSelectionButton extends UILStateButton{

  static final long serialVersionUID = 8532842007246228981L;

  protected UilClientSelectionBox box;

  UILSelectionButton(UilSelectionButton uilButton, UilClientSelectionBox box, Class staticClass) 
       throws G2AccessException{
    super(uilButton, null, staticClass);
    this.box = box;
  }

  protected UILSelectionButton(UilSelectionButton uilButton, UilClientSelectionBox box, CheckboxGroup group, 
			       Class staticClass) throws G2AccessException{
    super(uilButton, group, staticClass);
    this.box = box;
  }

  public UilClientSelectionBox getSelectionBox(){
    return box;
  }
}
