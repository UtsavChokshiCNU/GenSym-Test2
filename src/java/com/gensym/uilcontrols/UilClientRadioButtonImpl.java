package com.gensym.uilcontrols;

import java.awt.Checkbox;
import java.lang.reflect.InvocationTargetException;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilRadioButton;

class UilClientRadioButtonImpl extends UilClientStateButtonImpl implements UilClientRadioButton{

  static final long serialVersionUID = -761491698608133079L;

  UilClientRadioButtonImpl(UilRadioButton uilButton, UILSelectionButton component, Class staticClass) 
       throws G2AccessException{
    super(uilButton, component, staticClass);
  }

  //uilToggleButton should only turn on the button if it was off
  @Override
  public void uilToggleButton(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (getToggleState().equals(OFF_))
      super.uilToggleButton(win);
    toggled();
  }

  @Override
  public void uilToggleButtonNoCallback(){
    if (getToggleState().equals(OFF_))
      super.uilToggleButtonNoCallback();
  }

  //this is called from component's setState method
  @Override
  public void setToggleState(Symbol state){
    if (state != null && (state.equals(UilClientConstants.ON_) || state.equals(UilClientConstants.OFF_))){
      if (!state.equals(getToggleState()))
	super.uilToggleButtonNoCallback();
    }
    else
      throw new IllegalArgumentException("state must be either ON or OFF");
  }

  //if onValue is match, toggleButton; otherwise turn off with no callback
  @Override
  protected boolean uppUpdateButtonFromSingleValue(Object value, boolean toggleOffNoMatch) 
       throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException,
	 IllegalAccessException{
    Symbol toggleState = getToggleState();
    Object onValue = getOnValue();
    if (value != null && 
	(value.equals(onValue) ||
	 (value instanceof String && ((String)value).indexOf(onValue.toString()) != -1))){
      if (!toggleState.equals(ON_))
		  super.uilToggleButton(getDialogProxy().getWindow());
      return true;
    }
    /* Can't do this:
       else if (toggleState.equals(ON_))
       setState(false);

       CheckboxGroup won't allow for having no radiobutton selected.
       Therefore, if no radiobutton matches the value and a radiobutton is selected, it 
       will NOT be unselected.  This differs from UIL.
       */
    return false;
  }
  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException{
    (((UILSelectionButton)getComponent()).getSelectionBox()).uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

  @Override
  public Object getUilEventSourceObject(){
    if (!((UILSelectionButton)getComponent()).getSelectionBox().getUilEventSourceObject().equals(UilClientConstants.UNSPECIFIED_))
      return ((UILSelectionButton)getComponent()).getSelectionBox().getUilEventSourceObject();
    else
      return super.getUilEventSourceObject();
  }

  @Override
  public Symbol getUilEventSourceAttribute(){
    //System.out.println("getSourceAttribute:"+((UILSelectionButton)getComponent()).getSelectionBox().getUilEventSourceAttribute());
    if (!((UILSelectionButton)getComponent()).getSelectionBox().getUilEventSourceAttribute().equals(UilClientConstants.UNSPECIFIED_))
      return ((UILSelectionButton)getComponent()).getSelectionBox().getUilEventSourceAttribute();
    else
      return super.getUilEventSourceAttribute();
  }

  @Override
  public Object getUilEventTargetObject(){
    if (!((UILSelectionButton)getComponent()).getSelectionBox().getUilEventTargetObject().equals(UilClientConstants.UNSPECIFIED_))
      return ((UILSelectionButton)getComponent()).getSelectionBox().getUilEventTargetObject();
    else
      return super.getUilEventTargetObject();
  }

  @Override
  public Symbol getUilEventTargetAttribute(){
    if (!((UILSelectionButton)getComponent()).getSelectionBox().getUilEventTargetAttribute().equals(UilClientConstants.UNSPECIFIED_))
      return ((UILSelectionButton)getComponent()).getSelectionBox().getUilEventTargetAttribute();
    else
      return super.getUilEventTargetAttribute();
  }

  @Override
  public Object getValue(){
    return (getToggleState().equals(ON_) ? getOnValue() : null);
  }
    
}
