package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;

public interface UilClientButton extends UilClientGrobj{

  //properties
  public Symbol getCallback();
  public Symbol getUilState();  //should be getState
  public Symbol getUilLabelSize();
  public Symbol getUilLabelConstant();
  public Symbol getUilTranslationConstraints();
  public String getUilShortDescription();
  public Symbol getUilHandlerMethod();

  //callbacks
  public UilCallback getButtonCallback();
  public void setButtonCallback(UilCallback callback);

  //API
  public void uilAddLabelToButton(String label, Symbol size);
  public void uilDisableButton();
  public void uilEnableButton();
  public void uilSelectButton(UiClientItem win, UilClientDialog dlg) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
}
