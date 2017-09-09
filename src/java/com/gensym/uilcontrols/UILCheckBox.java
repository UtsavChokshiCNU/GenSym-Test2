package com.gensym.uilcontrols;

import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilCheckBox;
import com.gensym.classes.modules.uilroot.UilSelectionButton;
import com.gensym.classes.modules.uillib.UilCheckButton;

public class UILCheckBox extends UILSelectionBox implements UilClientCheckBox{

  static final long serialVersionUID = 6624609674931514435L;

  public UILCheckBox(UilCheckBox uilCheckBox, Class staticClass) throws G2AccessException{
    super(uilCheckBox, staticClass);
    uilHelper = new UilClientCheckBoxImpl(uilCheckBox, this, staticClass);
  }

  @Override
  protected UILSelectionButton createSelectionButton(UilSelectionButton button) throws G2AccessException{
    return new UILCheckButton((UilCheckButton)button, this, staticClass);
  }

  //UilClientCheckBox interface
  //API
  @Override
  public Sequence uilGetCheckBoxValues(){
    return ((UilClientCheckBox)uilHelper).uilGetCheckBoxValues();
  }
  @Override
  public void uilSetCheckBoxValues(Sequence values){
    ((UilClientCheckBox)uilHelper).uilSetCheckBoxValues(values);
  }
}
