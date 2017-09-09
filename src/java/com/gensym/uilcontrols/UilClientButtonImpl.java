package com.gensym.uilcontrols;

import java.awt.Component;
import java.io.Serializable;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilButton;
import com.gensym.classes.modules.uilroot.UilSelectionButton;
import com.gensym.classes.modules.uildefs.UilIconToggleButton;
import com.gensym.classes.modules.uildefs.UilTextToggleButton;
import com.gensym.classes.modules.uillib.UilIconPushbutton;
import com.gensym.classes.modules.uillib.UilTextPushbutton;

abstract class UilClientButtonImpl extends UilClientGrobjImpl implements UilClientButton, Serializable{

  static final long serialVersionUID = -6048341635060492344L;

  private Symbol callback;
  private UilCallback buttonCallback;
  private Symbol state;
  private Symbol uilLabelSize;
  private Symbol uilLabelConstant;
  private Symbol uilTranslationConstraints;
  private String uilShortDescription;
  private Symbol uilHandlerMethod;

  public UilClientButtonImpl(UilButton uilButton, Component component, Class staticClass) 
       throws G2AccessException{
    super(uilButton, component, staticClass);
    callback = getCallback(uilButton);
    state = (Symbol)uilButton.getState();
    uilLabelSize = (Symbol)uilButton.getUilLabelSize();
    uilLabelConstant = (Symbol)uilButton.getUilLabelConstant();
    uilTranslationConstraints = (Symbol)uilButton.getUilTranslationConstraints();
    uilShortDescription = (String)uilButton.getUilShortDescription();
    uilHandlerMethod = (Symbol)uilButton.getUilHandlerMethod();
  }

  private Symbol getCallback(UilButton uilButton) throws G2AccessException{
    if (uilButton instanceof UilIconPushbutton)
      return (Symbol)((UilIconPushbutton)uilButton).getCallback();
    else if (uilButton instanceof UilTextPushbutton)
      return (Symbol)((UilTextPushbutton)uilButton).getCallback();
    else if (uilButton instanceof UilIconToggleButton)
      return (Symbol)((UilIconToggleButton)uilButton).getCallback();
    else if (uilButton instanceof UilTextToggleButton)
      return (Symbol)((UilTextToggleButton)uilButton).getCallback();
    else if (uilButton instanceof UilSelectionButton)
      return (Symbol)((UilSelectionButton)uilButton).getCallback();
    else throw new IllegalArgumentException("Expected "+uilButton+" to be a UilIconPushbutton, UilTextPushbutton, UilIconToggleButton, UilTextToggleButton, or a UilSelectionButton");
  }

  @Override
  public Symbol getCallback(){
    return callback;
  }

  @Override
  public UilCallback getButtonCallback(){
    return buttonCallback;
  }

  @Override
  public void setButtonCallback(UilCallback callback){
    buttonCallback = callback;
  }
  
  @Override
  public Symbol getUilState(){
    return state;
  }

  @Override
  public Symbol getUilLabelSize(){
    return uilLabelSize;
  }

  @Override
  public Symbol getUilLabelConstant(){
    return uilLabelConstant;
  }

  @Override
  public Symbol getUilTranslationConstraints(){
    return uilTranslationConstraints;
  }

  @Override
  public String getUilShortDescription(){
    return uilShortDescription;
  }

  @Override
  public Symbol getUilHandlerMethod(){
    return uilHandlerMethod;
  }

  @Override
  public void uilDisableButton(){
    getComponent().setEnabled(false);
  }

  @Override
  public void uilEnableButton(){
    getComponent().setEnabled(true);
  }
  
}

