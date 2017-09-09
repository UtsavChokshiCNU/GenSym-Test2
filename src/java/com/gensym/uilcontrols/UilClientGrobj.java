package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;

public interface UilClientGrobj extends UilClientItem{
  
  //properties
  public Symbol getUilValidationMethod();
  public Symbol getUilConcludeMethod();

  //callbacks
  public UilCallback getValidationCallback();
  public void setValidationCallback(UilCallback callback);
  public UilCallback getConcludeCallback();
  public void setConcludeCallback(UilCallback callback);

  //API
  public String uilCallValidateMethodForGrobj(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public String uilValidateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
				       Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
				 Object actionQueue);
  public void uilCallConcludeMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
				     Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException;
}
