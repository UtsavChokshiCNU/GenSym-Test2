package com.gensym.uilcontrols;

import java.awt.Component;
import com.gensym.widgets.Border;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilBoxBorder;


class UilClientBorderImpl extends UilClientGrobjImpl implements UilClientBorder{

  static final long serialVersionUID = 2258966053749731086L;

  UilClientBorderImpl(UilBoxBorder uilBoxBorder, Border component, Class staticClass) 
       throws G2AccessException{
    super(uilBoxBorder, component, staticClass);
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
