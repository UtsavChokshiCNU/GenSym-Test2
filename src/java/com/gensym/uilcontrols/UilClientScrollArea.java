package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.G2List;
import com.gensym.classes.G2Array;

public interface UilClientScrollArea extends UilClientGrobj{

  //properties
  public Symbol getOrderingMethod();
  public int getMaximumAllowedMessages();
  public Symbol getUilMessageSelectionMethod();
  public Symbol getUilMessageUnselectionMethod();
  public Symbol getUilScrollIncrementMethod();
  public Symbol getUilScrollDecrementMethod();
  public Symbol getUilScrollIncrementLineMethod();
  public Symbol getUilScrollDecrementLineMethod();
  public Symbol getUilScrollToPositionMethod();
  public boolean getAllowMultipleSimultaneousSelections();
  public boolean getAllowUnselectOnSelectedMessage();
  public Symbol getUilUpdateStyle();
  public Symbol getUilConcludeStyle();
  public Object getUilMaximumCharactersToDisplay();//Symbol or Integer
  public boolean getUilAllowManualMessageMove();
  public Symbol getUilFormatSpecification();
  public boolean getUilDisplayDisabledMessages();
  public boolean getUilUpdateValue();

  //callbacks
  public UilCallback getUilMessageSelectionCallback();
  public void setUilMessageSelectionCallback(UilCallback callback);
  public UilCallback getUilMessageUnselectionCallback();
  public void setUilMessageUnselectionCallback(UilCallback callback);

  //API
  public UilClientMessageObject uilCreateMessageObject(Object value, double quantity);
  public void uilRemoveMessage(UilClientMessageObject msgObject);
  public void uilClearMessages();
  public void uilDeleteSelectedMessages();
  public void uilDisplayMessageList(int index);
  public int uilGetIndexOfScrollMessage(UilClientMessageObject msgObject);
  public UilClientMessageObject uilGetMessageFromIndex(int index);
  public void uilSelectMessage(UilClientMessageObject msgObject) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilUnselectMessage(UilClientMessageObject msgObject);
  public void uilMessageSelection(UilClientMessageObject msgObject, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException;
  public void uilMessageSelectionMethod(UilClientMessageObject msgObject, UiClientItem win) throws  G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException;
  public void uilMessageUnselection(UilClientMessageObject msgObject,  UiClientItem win);
  public void uilMessageUnselectionMethod(UilClientMessageObject msgObject, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException;
  public void uilResetScrollArea();
  public Symbol uilAddMessageToList(UilClientMessageObject msgObject);
  public void uilUpdateScrollAreaFromList(G2List list) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilUpdateScrollAreaFromArray(G2Array array) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public String[] uilGetSelectedMessage();
  public UilClientMessageObject[] uilGetSelectedMessageObjects();
  public String[] getMessages();
  public UilClientMessageObject[] getMessageObjects();
  public void updateFromSequence(Sequence list) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilUpdateMessageText(UilClientMessageObject msgObject, String text);
}
