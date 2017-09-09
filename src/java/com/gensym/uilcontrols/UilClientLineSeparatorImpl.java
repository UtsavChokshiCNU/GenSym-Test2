package com.gensym.uilcontrols;

import java.awt.Component;
import com.gensym.widgets.Border;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilLineSeparator;

class UilClientLineSeparatorImpl extends UilClientGrobjImpl implements UilClientLineSeparator{

  static final long serialVersionUID = -804459787671338838L;  

  private Symbol orientation;

  UilClientLineSeparatorImpl(UilLineSeparator uilLineSeparator, Border component, Class staticClass) 
       throws G2AccessException{
    super(uilLineSeparator, component, staticClass);
    orientation = (Symbol)uilLineSeparator.getOrientation();
  }

  //properties
  @Override
  public Symbol getOrientation(){
    return orientation;
  }

  //API
  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, Object actionQueue) throws G2AccessException{
    //do nothing
  }

  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, Object actionQueue) throws G2AccessException{
    //do nothing
  }
}
