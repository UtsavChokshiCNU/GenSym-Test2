package com.gensym.uilcontrols;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilCheckBox;

class UilClientCheckBoxImpl extends UilClientSelectionBoxImpl implements UilClientCheckBox{

  static final long serialVersionUID = -4447191966991348298L;

  UilClientCheckBoxImpl(UilCheckBox uilCheckBox, UILCheckBox checkBox,
			Class staticClass) throws G2AccessException{
    super(uilCheckBox, checkBox, staticClass);
  }

  @Override
  public Sequence uilGetCheckBoxValues(){
    UilClientStateButton[] buttons = ((UILCheckBox)getComponent()).getMembers();
    Sequence values = new Sequence();
    for (int i=0; i<buttons.length; i++)
      if (buttons[i].getToggleState().equals(buttons[i].ON_))
	values.addElement(buttons[i].getOnValue());
    return values;
  }

  @Override
  public void uilSetCheckBoxValues(Sequence values){
    //to do
  }

  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException{
    if (membersHaveSameTarget()){
      UilClientStateButton[] buttons = ((UILSelectionBox)getComponent()).getMembers();
      buttons[0].uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
    }
    else
      super.uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

  private boolean membersHaveSameTarget(){
    UilClientStateButton[] buttons = ((UILSelectionBox)getComponent()).getMembers();
    boolean sameTarget = true;
    UilClientStateButton leadButton = buttons[0];
    for (int i=1; i<buttons.length; i++){
      if (!leadButton.getUilEventTargetObject().equals(buttons[i].getUilEventTargetObject()) ||
	  !leadButton.getUilEventTargetAttribute().equals(buttons[i].getUilEventTargetAttribute())){
	sameTarget = false;
	break;
      }
    }
    return sameTarget;
  }

  //misc
  @Override
  public Sequence getValues(){
    return uilGetCheckBoxValues();
  }
}
