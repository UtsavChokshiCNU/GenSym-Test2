package com.gensym.uilcontrols;

import java.awt.Component;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;

public interface UilClientItem{

  //properties
  public String getId();
  public Object getUserData();
  public void setUserData(Object data);
  public Object getUilEventSourceObject(); //string or symbol
  public Symbol getUilEventSourceAttribute();
  public Object getUilEventTargetObject(); //string or symbol
  public Symbol getUilEventTargetAttribute();

  public Symbol getConfiguration();
  public Symbol getUilSize();
  public boolean getUilConcludeValueImmediately();

  public Symbol getUilInitializationMethod();
  public Symbol getUilEnableMethod();
  public Symbol getUilDisableMethod();
  public Symbol getUilSizeOfMethod();
  public Symbol getUilConfigurationMethod();
  public Symbol getUilCloneMethod();
  public Symbol getUilManageMethod();
  public Symbol getUilUpdateMethod();
  public Symbol getUilDeleteMethod();

  //callbacks
  public UilCallback getUpdateCallback();
  public void setUpdateCallback(UilCallback callback);
  public UilCallback getEnableCallback();
  public void setEnableCallback(UilCallback callback);
  public UilCallback getDisableCallback();
  public void setDisableCallback(UilCallback callback);

  //API
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException;
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilDisableGrobj();
  public void uilDisableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilEnableGrobj();
  public void uilEnableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;

  //misc
  public void setDialogProxy(UilClientDialog dlg);
  public UilClientDialog getDialogProxy();
}

