package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.widgets.TextWidget;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;

public interface UilClientEditBox extends UilClientGrmes{

  //properties
  public Symbol getUilEditStyle();
  public boolean getUilAllowFieldEditOfThisMessage();
  public Symbol getUilFormatSpecification();
  public boolean getUilClearTextBeforeEdit();
  public Symbol getUilConcludeMethod();
  public boolean getUilValidateValueImmediately();
  public Symbol getUilValidationMethod();
  public Symbol getUilMessageSelectionMethod();
  public Symbol getUilMessageUnselectionMethod();
  public String getLabel();
  public Symbol getUilState();
  public String getMessageContents();
  public void setMessageContents(String txt);
  public boolean getUilUpdateValue();
  public Boolean getUilUseGrammarPerTargetSpecifications();

  public void setLabel(String label);

  //callbacks
  public UilCallback getConcludeCallback();
  public void setConcludeCallback(UilCallback callback);
  public UilCallback getValidationCallback();
  public void setValidationCallback(UilCallback callback);
  public UilCallback getMessageSelectionCallback();
  public void setMessageSelectionCallback(UilCallback callback);
  public UilCallback getMessageUnselectionCallback();
  public void setMessageUnselectionCallback(UilCallback callback);

  //API
  public String uilCallValidateMethodForGrobj(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public String uilValidateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				       Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object button, Object actionQueue);
  public void uilCallConcludeMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				     Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object button, Object actionQueue) 
       throws G2AccessException;
  public Object uilGetEditBoxValue();
  public void uilUpdateEditBoxLabel();
  public void uilEditBoxSelection(UilClientDialog dlg, UiClientItem win);
  public void uilEditBoxSelectionMethod(UilClientDialog dlg, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilEditBoxUnselection(UilClientDialog dlg, UiClientItem win, Boolean committed) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilEditBoxUnselectionMethod(UilClientDialog dlg, UiClientItem win, Boolean committed) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilSelectEditBox(UilClientDialog dlg, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilSelectEditBoxOnDialog(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;

  //misc
  public void setLabelComponent(TextWidget text);
  public TextWidget getLabelComponent();
}
