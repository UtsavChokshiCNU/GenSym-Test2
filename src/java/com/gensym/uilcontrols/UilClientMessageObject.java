package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;

public interface UilClientMessageObject extends UilClientGrmes{

  //properties
  public double getMessageDisplayPriority();
  public Symbol getUilConcludeMethod();
  public Symbol getUilMessageSelectionMethod();
  public Symbol getUilMessageUnselectionMethod();
  public Symbol getUilFormatSpecification();
  public Symbol getUilEditStyle();
  public String getMessageContents();
  public boolean getUilUpdateValue();
  public long getUilTimeStamp();

  //API
  public void uilCallConcludeMethodForGrobj(UiClientItem win) 
       throws G2AccessException;
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
					    Object actionQueue)  throws G2AccessException;
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg,
				      Object buttonOrInitObj, Object actionQueue) throws G2AccessException;
  public Symbol uilGetMessageObjectState();
  public void uilSelectMessage() throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilSelectMessageOnWindow(UiClientItem win)throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilUnselectMessage();
  public void uilRemoveMessage();
  public void uilRemoveMessageFromList();
}
