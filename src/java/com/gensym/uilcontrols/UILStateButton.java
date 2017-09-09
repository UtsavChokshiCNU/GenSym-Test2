package com.gensym.uilcontrols;

import java.awt.Checkbox;
import java.awt.CheckboxGroup;
import java.awt.Component;
import java.util.Enumeration;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uildefs.UilTextToggleButton;
import com.gensym.classes.modules.uildefs.UilIconToggleButton;
import com.gensym.classes.modules.uilroot.UilSelectionButton;


public abstract class UILStateButton extends Checkbox implements UilClientStateButton, Serializable{

  static final long serialVersionUID = -6080611903458859135L;

  protected UilClientStateButton uilHelper;

  UILStateButton(UilTextToggleButton uilButton, Class staticClass) throws G2AccessException{
    uilHelper = new UilClientStateButtonImpl(uilButton, this, staticClass);
    init();
  }

  UILStateButton(UilIconToggleButton uilButton, Class staticClass) throws G2AccessException{
    uilHelper = new UilClientStateButtonImpl(uilButton, this, staticClass);
    init();
  }

  protected UILStateButton(UilSelectionButton uilButton, CheckboxGroup group, Class staticClass) 
       throws G2AccessException{
    super("", false, group);
    uilHelper = new UilClientStateButtonImpl(uilButton, this, staticClass);
    init();
  }

  private void init(){
    setLabel(uilHelper.getUilLabel());
    setState0(getToggleState().equals(ON_) ? true : false);
  }

  @Override
  public void setState(boolean state){
    if (state != getState()){
	super.setState(state);
	uilHelper.setToggleState(state ? ON_ : OFF_);
    }
  }

  void setState0(boolean state){
    super.setState(state);
  }
  
  @Override
  public String toString(){
    return getClass().getName()+"[id="+getId()+" label="+getLabel()+"]";
  }

  //UilClientStateButton interface
  //properties
  @Override
  public String getId(){
    return uilHelper.getId();
  }
  @Override
  public Object getUserData(){
    return uilHelper.getUserData();
  }
  @Override
  public void setUserData(Object data){
    uilHelper.setUserData(data);
  }
  @Override
  public Object getUilEventSourceObject(){
    return uilHelper.getUilEventSourceObject();
  }
  @Override
  public Symbol getUilEventSourceAttribute(){
    return uilHelper.getUilEventSourceAttribute();
  }
  @Override
  public Object getUilEventTargetObject(){
    return uilHelper.getUilEventTargetObject();
  }
  @Override
  public Symbol getUilEventTargetAttribute(){
    return uilHelper.getUilEventTargetAttribute();
  }
  @Override
  public Symbol getConfiguration(){
    return uilHelper.getConfiguration();
  }
  @Override
  public Symbol getUilSize(){
    return uilHelper.getUilSize();
  }
  @Override
  public boolean getUilConcludeValueImmediately(){
    return uilHelper.getUilConcludeValueImmediately();
  }
  @Override
  public Symbol getUilInitializationMethod(){
    return uilHelper.getUilInitializationMethod();
  }
  @Override
  public Symbol getUilEnableMethod(){
    return uilHelper.getUilEnableMethod();
  }
  @Override
  public Symbol getUilDisableMethod(){
    return uilHelper.getUilDisableMethod();
  }
  @Override
  public Symbol getUilSizeOfMethod(){
    return uilHelper.getUilSizeOfMethod();
  }
  @Override
  public Symbol getUilConfigurationMethod(){
    return uilHelper.getUilConfigurationMethod();
  }
  @Override
  public Symbol getUilCloneMethod(){
    return uilHelper.getUilCloneMethod();
  }
  @Override
  public Symbol getUilManageMethod(){
    return uilHelper.getUilManageMethod();
  }
  @Override
  public Symbol getUilUpdateMethod(){
    return uilHelper.getUilUpdateMethod();
  }
  @Override
  public Symbol getUilDeleteMethod(){
    return uilHelper.getUilDeleteMethod();
  }
  @Override
  public UilCallback getUpdateCallback(){
    return uilHelper.getUpdateCallback();
  }
  @Override
  public void setUpdateCallback(UilCallback callback){
    uilHelper.setUpdateCallback(callback);
  }
  @Override
  public UilCallback getEnableCallback(){
    return uilHelper.getEnableCallback();
  }
  @Override
  public void setEnableCallback(UilCallback callback){
    uilHelper.setEnableCallback(callback);
  }
  @Override
  public UilCallback getDisableCallback(){
    return uilHelper.getDisableCallback();
  }
  @Override
  public void setDisableCallback(UilCallback callback){
    uilHelper.setDisableCallback(callback);
  }
  @Override
  public Symbol getUilValidationMethod(){
    return uilHelper.getUilValidationMethod();
  }
  @Override
  public UilCallback getValidationCallback(){
    return uilHelper.getValidationCallback();
  }
  @Override
  public void setValidationCallback(UilCallback callback){
    uilHelper.setValidationCallback(callback);
  }
  @Override
  public Symbol getUilConcludeMethod(){
    return uilHelper.getUilConcludeMethod();
  }
  @Override
  public UilCallback getConcludeCallback(){
    return uilHelper.getConcludeCallback();
  }
  @Override
  public void setConcludeCallback(UilCallback callback){
    uilHelper.setConcludeCallback(callback);
  }
  @Override
  public Symbol getCallback(){
    return uilHelper.getCallback();
  }
  @Override
  public UilCallback getButtonCallback(){
    return uilHelper.getButtonCallback();
  }
  @Override
  public void setButtonCallback(UilCallback callback){
    uilHelper.setButtonCallback(callback);
  }
  @Override
  public Symbol getUilState(){
  return uilHelper.getUilState();
  }
  @Override
  public Symbol getUilLabelSize(){
    return uilHelper.getUilLabelSize();
  }
  @Override
  public Symbol getUilLabelConstant(){
    return uilHelper.getUilLabelConstant();
  }
  @Override
  public Symbol getUilTranslationConstraints(){
    return uilHelper.getUilTranslationConstraints();
  }
  @Override
  public String getUilShortDescription(){
    return uilHelper.getUilShortDescription();
  }
  @Override
  public Symbol getUilHandlerMethod(){
    return uilHelper.getUilHandlerMethod();
  }
  @Override
  public String getUilLabel(){
    return uilHelper.getUilLabel();
  }
  @Override
  public void setUilLabel(String label){
    uilHelper.setUilLabel(label);
  }
  @Override
  public Symbol getToggleState(){
    return uilHelper.getToggleState();
  }
  @Override
  public void setToggleState(Symbol state){
    uilHelper.setToggleState(state);
  }
  @Override
  public Object getOnValue(){
    return uilHelper.getOnValue();
  }
  @Override
  public Object getOffValue(){
    return uilHelper.getOffValue();
  }
  @Override
  public boolean getUilUpdateValue(){
    return uilHelper.getUilUpdateValue();
  }
 
  //API
  @Override
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallUpdateMethodForGrobj(win);
  }
  @Override
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilUpdateGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			     Object actionQueue) throws G2AccessException{
    uilHelper.uilUpdateGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public void uilDisableGrobjMethod()throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilDisableGrobjMethod();
  }
  @Override
  public void uilDisableGrobj(){
    uilHelper.uilDisableGrobj();
  }
  @Override
  public void uilEnableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilEnableGrobjMethod();
  }
  @Override
  public void uilEnableGrobj(){
    uilHelper.uilEnableGrobj();
  }
  @Override
  public void setDialogProxy(UilClientDialog dlg){
    uilHelper.setDialogProxy(dlg);
  }
  @Override
  public UilClientDialog getDialogProxy(){
    return uilHelper.getDialogProxy();
  }
  @Override
  public String uilCallValidateMethodForGrobj(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilHelper.uilCallValidateMethodForGrobj(win);
  }
  @Override
  public String uilValidateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
					 Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilHelper.uilValidateGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
				 Object actionQueue){
    return uilHelper.uilValidateGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public void uilCallConcludeMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallConcludeMethodForGrobj(win);
  }
  @Override
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				     Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilConcludeGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			       Object actionQueue) throws G2AccessException{
    uilHelper.uilConcludeGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public void uilAddLabelToButton(String label, Symbol size){
    uilHelper.uilAddLabelToButton(label, size);
  }
  @Override
  public void uilDisableButton(){
    uilHelper.uilDisableButton();
  }
  @Override
  public void uilEnableButton(){
    uilHelper.uilEnableButton();
  }
  @Override
  public void uilSelectButton(UiClientItem win, UilClientDialog dlg) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilSelectButton(win, dlg);
  }
  @Override
  public void uilToggleButton(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilToggleButton(win);
  }
  @Override
  public void uilToggleButtonNoCallback(){
    uilHelper.uilToggleButtonNoCallback();
  }
}
