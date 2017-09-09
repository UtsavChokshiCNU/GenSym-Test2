package com.gensym.uilcontrols;

import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilCheckButton;

class UilClientCheckButtonImpl extends UilClientStateButtonImpl{

  static final long serialVersionUID = 7920169867532318192L;

  UilClientCheckButtonImpl(UilCheckButton uilButton, UILSelectionButton component, Class staticClass) 
       throws G2AccessException{
    super(uilButton, component, staticClass);
  }

  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException{
    UILSelectionBox box = (UILSelectionBox)((UILSelectionButton)getComponent()).getSelectionBox();
    UilClientStateButton[] buttons = box.getMembers();
    boolean sameTarget = true;
    for (int i=0; i<buttons.length; i++){
      if (!getUilEventTargetObject().equals(buttons[i].getUilEventTargetObject()) ||
	  !getUilEventTargetAttribute().equals(buttons[i].getUilEventTargetAttribute())){
	sameTarget = false;
	break;
      }
    }
    if (sameTarget){
      Sequence values = ((UilClientCheckBox)((UILSelectionButton)getComponent()).getSelectionBox()).uilGetCheckBoxValues();
      Item targetObject = getTargetObject();
      Symbol targetAttributeName = getUilEventTargetAttribute();
      try{
	if (targetAttributeName != null && !targetAttributeName.equals(UilClientConstants.UNSPECIFIED_)){
	  Object currentValue = targetObject.getPropertyValue(targetAttributeName);
	  if (isValue(currentValue))
	    concludeSequenceToAttribute(targetObject, targetAttributeName, values);
	  else
	    concludeSequenceToItem(currentValue, values);
	}
	else
	  concludeSequenceToItem(targetObject, values);
      }
      catch(NoSuchAttributeException ex){
	concludeSequenceToItem(targetObject, values);
      }
    }
    else
      super.uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

}
