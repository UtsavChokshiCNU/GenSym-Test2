package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.Checkbox;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.util.Enumeration;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.UnexpectedException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.Item;
import com.gensym.classes.G2Array;
import com.gensym.classes.G2List;
import com.gensym.classes.ValueArray;
import com.gensym.classes.ValueList;
import com.gensym.classes.ItemArray;
import com.gensym.classes.ItemList;
import com.gensym.classes.modules.uildefs.UilIconToggleButton;
import com.gensym.classes.modules.uildefs.UilTextToggleButton;
import com.gensym.classes.modules.uilroot.UilSelectionButton;

class UilClientStateButtonImpl extends UilClientButtonImpl implements UilClientStateButton, ItemListener, Serializable{
  
  static final long serialVersionUID = 5737771536227244560L;

  private String label;
  private Symbol toggleState;
  private Object onValue;
  private Object offValue;
  private boolean uilUpdateValue;
  
  UilClientStateButtonImpl(UilIconToggleButton uilButton, UILStateButton component,
			   Class staticClass) throws G2AccessException{
    super(uilButton, component, staticClass);
    label = (String)uilButton.getLabel();
    toggleState = (Symbol)uilButton.getToggleState();
    onValue = uilButton.getOnValue();
    offValue = uilButton.getOffValue();
    uilUpdateValue = ((Boolean)uilButton.getUilUpdateValue()).booleanValue();
    init(staticClass);
  }

  UilClientStateButtonImpl(UilTextToggleButton uilButton, Checkbox component,
			   Class staticClass) throws G2AccessException{
    super(uilButton, component, staticClass);
    label = (String)uilButton.getLabel();
    toggleState = (Symbol)uilButton.getToggleState();
    onValue = uilButton.getOnValue();
    offValue = uilButton.getOffValue();
    uilUpdateValue = ((Boolean)uilButton.getUilUpdateValue()).booleanValue();
    init(staticClass);
  }

  UilClientStateButtonImpl(UilSelectionButton uilButton, Checkbox component,
			   Class staticClass) throws G2AccessException{
    super(uilButton, component, staticClass);
    label = (String)uilButton.getLabel();
    toggleState = (Symbol)uilButton.getToggleState();
    onValue = uilButton.getOnValue();
    offValue = uilButton.getOffValue();
    uilUpdateValue = ((Boolean)uilButton.getUilUpdateValue()).booleanValue();
    init(staticClass);
  }

  private void init(Class staticClass){
    Symbol callbackName = getCallback();
    if ( UilClientConstants.UIL_DO_NOTHING_.equals(callbackName))
      setButtonCallback(new UilCallback(callbackName, UilClientConstants.CALLBACK_ARG_TYPES, 
					UilClientConstants.CALLBACK_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(callbackName);
      setButtonCallback(new UilCallback(callbackName,  UilClientConstants.CALLBACK_ARG_TYPES, 
					UilClientConstants.CALLBACK_ARGS, 
					staticClass, methodName));
    }

    Checkbox checkbox = (Checkbox)getComponent();
    checkbox.addItemListener(this);
  }
  
  @Override
  public void itemStateChanged(ItemEvent event){
    if (java.beans.Beans.isDesignTime()) return;
    try{
      if (event.getStateChange() == event.SELECTED)
	setButtonStateOn(true);
      else
	setButtonStateOff(true);
    }
    catch(G2AccessException ex){
      throw new UnexpectedException(ex);
    }
    catch(ClassNotFoundException cnfe){
      throw new UnexpectedException(cnfe);
    }
    catch(InvocationTargetException ite){
      throw new UnexpectedException(ite);
    }
    catch(NoSuchMethodException nsme){
      throw new UnexpectedException(nsme);
    }
    catch(IllegalAccessException iae){
      throw new UnexpectedException(iae);
    }
  }

  //properties
  @Override
  public String getUilLabel(){
    return label;
  }

  @Override
  public void setUilLabel(String label){
    this.label = label;
  }

  @Override
  public Symbol getToggleState(){
    return toggleState;
  }

  @Override
  public void setToggleState(Symbol state){
    if (state != null && (state.equals(UilClientConstants.ON_) || state.equals(UilClientConstants.OFF_))){
      if (!state.equals(toggleState))
	uilToggleButtonNoCallback();
    }
    else
      throw new IllegalArgumentException("state must be either ON or OFF");
  }

  @Override
  public Object getOnValue(){
    return onValue;
  }

  @Override
  public Object getOffValue(){
    return offValue;
  }

  @Override
  public boolean getUilUpdateValue(){
    return uilUpdateValue;
  }

  //API
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException{
			       //System.out.println("UilClientStateButtonImpl.uilUpdateGrobj");
    if (!uilUpdateValue) return;
    Item sourceObject = getSourceObject();
    if (sourceObject == null) return;
    try{
      Object value = null;
      Symbol sourceAttributeName = getUilEventSourceAttribute();
      try{
	if (sourceAttributeName != null && !sourceAttributeName.equals( UilClientConstants.UNSPECIFIED_)){
	  value = sourceObject.getPropertyValue(sourceAttributeName);
	  if (isValue(value))
	    uppUpdateButtonFromSingleValue(value, true);
	  else
	    uppUpdateButtonFromItem(value);
	}
	else
	  uppUpdateButtonFromItem(sourceObject);
      }
      catch(NoSuchAttributeException ex){
	uppUpdateButtonFromItem(sourceObject);
      }
    }
    catch(ClassNotFoundException cnfe){
      throw new UnexpectedException(cnfe);
    }
    catch(InvocationTargetException ite){
      throw new UnexpectedException(ite);
    }
    catch(NoSuchMethodException nsme){
      throw new UnexpectedException(nsme);
    }
    catch(IllegalAccessException iae){
      throw new UnexpectedException(iae);
    }
  }
  
  protected boolean uppUpdateButtonFromSingleValue(Object value, boolean toggleOffNoMatch) 
       throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException,
	 IllegalAccessException{
    if (value != null && (value.equals(onValue) ||
	(value instanceof String && ((String)value).indexOf(onValue.toString()) != -1))){
      if (!toggleState.equals(ON_))
	setButtonStateOn(true);
      return true;
    }
    else {
      if (value != null && (value.equals(offValue) ||
	  (value instanceof String && ((String)value).indexOf(offValue.toString()) != -1))){
	if (!toggleState.equals(OFF_))
	  setButtonStateOff(true);
	return true;
      }
      else if (toggleOffNoMatch && toggleState.equals(ON_))
	setButtonStateOff(true);
      return false;
    }
  }

  private void uppUpdateButtonFromItem(Object item) throws G2AccessException, ClassNotFoundException, 
	   InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (item instanceof G2List || item instanceof G2Array){
      Sequence list = null;
      if (item instanceof ItemList || item instanceof ValueList)
	list = getValuesFromSequence(((G2List)item).getG2ListSequence());
      else if (item instanceof ItemArray || item instanceof ValueArray)
	list = getValuesFromSequence(((G2Array)item).getG2ArraySequence());
      if (list != null)
	uppUpdateButtonFromSequence(list);
    }
    else{
      Object value = uppExtractValue(item);
      if (value != null)
	uppUpdateButtonFromSingleValue(value, true);
    }
  }

  private void uppUpdateButtonFromSequence(Sequence list) throws G2AccessException, ClassNotFoundException,
	     InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    Enumeration values = list.elements();
    boolean match = false;
    while (values.hasMoreElements()){
      match = uppUpdateButtonFromSingleValue(values.nextElement(), false);
      if (match) break;
    }
    if (!match && toggleState.equals(ON_))
      setButtonStateOff(true);
  }

  @Override
  public void uilAddLabelToButton(String label, Symbol size){
    ((Checkbox)getComponent()).setLabel(label);
  }

  @Override
  public void uilSelectButton(UiClientItem win, UilClientDialog dlg) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilToggleButton(win);
  }

  @Override
  public void uilToggleButton(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (getToggleState().equals(OFF_))
      setButtonStateOn(true);
    else
      setButtonStateOff(true);
  }

  @Override
  public void uilToggleButtonNoCallback(){
    try{
      if (getToggleState().equals(OFF_))
	setButtonStateOn(false);
      else
	setButtonStateOff(false);    
    }
    catch(G2AccessException ex){
      //this should never happen because toggled() is not called
    }
    catch(ClassNotFoundException cnfe){
    }
    catch(InvocationTargetException ite){
    }
    catch(NoSuchMethodException nsme){
    }
    catch(IllegalAccessException iae){
    }
  }
  

  protected void setButtonStateOn(boolean callback) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    //System.out.println("UilClientStateButtonImpl:"+getUilLabel()+".setButtonStateOn("+callback+")");
    ((UILStateButton)getComponent()).setState0(true);
    toggleState = ON_;
    //System.out.println(toggleState);
    if (callback) toggled();
  }

  protected void setButtonStateOff(boolean callback) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    //System.out.println("UilClientStateButtonImpl:"+getUilLabel()+".setButtonStateOff("+callback+")");
    ((UILStateButton)getComponent()).setState0(false);
    toggleState = OFF_;
    //System.out.println(toggleState);
    if (callback) toggled();
  }

  protected void toggled() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
	   //System.out.println("toggled:"+getUilLabel());
    UilClientDialog dlg = getDialogProxy();
    UilCallback callback = getButtonCallback();
    if (callback != null && !callback.isDefaultCallback() && dlg != null)
      callback.doCallback(new Object[]{this, dlg.getWindow(), dlg});
    if (getUilConcludeValueImmediately() && dlg != null)
      uilCallConcludeMethodForGrobj(dlg.getWindow());
  }

  @Override
  public Object getValue(){
    return (getToggleState().equals(ON_) ? getOnValue(): getOffValue());
  }
  
}
