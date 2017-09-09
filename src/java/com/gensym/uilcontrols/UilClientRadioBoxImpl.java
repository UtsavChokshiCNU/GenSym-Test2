package com.gensym.uilcontrols;

import java.awt.Component;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilRadioBox;

class UilClientRadioBoxImpl extends UilClientSelectionBoxImpl implements UilClientRadioBox{

  static final long serialVersionUID = 527410057410395675L;

  UilClientRadioBoxImpl(UilRadioBox uilRadioBox, UILRadioBox radioBox,
			Class staticClass) throws G2AccessException{
    super(uilRadioBox, radioBox, staticClass);
  }

  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException{
    uppConcludeValueToTarget();
  }

  //API
  @Override
  public Object uilGetRadioBoxValue(){
    return ((UILRadioBox)getComponent()).getCurrentValue();
  }

  @Override
  public void uilSetRadioBoxValue(Object value) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    UilClientStateButton[] buttons = ((UILRadioBox)getComponent()).getMembers();
    for (int i=0; i<buttons.length; i++){
      if (buttons[i].getOnValue().equals(value)){
	UilClientDialog dlg = getDialogProxy();
	if (dlg != null)
	  buttons[i].uilSelectButton(dlg.getWindow(), dlg);
	break;
      }
    }
  }

  //misc
  @Override
  public Object getValue(){
    return uilGetRadioBoxValue();
  }
}






