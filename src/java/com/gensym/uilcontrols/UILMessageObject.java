package com.gensym.uilcontrols;

import java.awt.Component;
import java.util.Date;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilsa.UilMessageObject;

class UILMessageObject extends UilClientGrmesImpl implements UilClientMessageObject{

 static final long serialVersionUID = 2366270222937211050L;

  private double messageDisplayPriority = 0.0;
  private Symbol uilConcludeMethod;
  private Symbol uilMessageSelectionMethod;
  private Symbol uilMessageUnselectionMethod;
  private Symbol uilFormatSpecification;
  private Symbol uilEditStyle;
  private String messageContents;
  private boolean uilUpdateValue = true;
  private long uilTimeStamp;

  //misc
  private UilClientScrollArea parent;


  UILMessageObject(UilClientScrollArea parent, UilMessageObject uilMsgObject, Class staticClass) 
       throws G2AccessException{
    super(uilMsgObject, null, staticClass);
    messageDisplayPriority = ((Number)uilMsgObject.getMessageDisplayPriority()).doubleValue();
    uilConcludeMethod = (Symbol)uilMsgObject.getUilConcludeMethod();
    uilMessageSelectionMethod = (Symbol)uilMsgObject.getUilMessageSelectionMethod();
    uilMessageUnselectionMethod = (Symbol)uilMsgObject.getUilMessageUnselectionMethod();
    uilFormatSpecification = (Symbol)uilMsgObject.getUilFormatSpecification();
    uilEditStyle = (Symbol)uilMsgObject.getUilEditStyle();
    messageContents = (String)uilMsgObject.getMessageContents();
    uilUpdateValue = ((Boolean)uilMsgObject.getUilUpdateValue()).booleanValue();
    uilTimeStamp = new Date().getTime();
    this.parent = parent;
  }

  UILMessageObject(UilClientScrollArea parent, Object value, double priority){
    this.parent = parent;
    messageContents = value.toString();
    messageDisplayPriority = priority;
    uilTimeStamp = new Date().getTime();
  }

  @Override
  public double getMessageDisplayPriority(){
    return messageDisplayPriority;
  }

  @Override
  public Symbol getUilConcludeMethod(){
    return uilConcludeMethod;
  }

  @Override
  public Symbol getUilMessageSelectionMethod(){
    return uilMessageSelectionMethod;
  }

  @Override
  public Symbol getUilMessageUnselectionMethod(){
    return uilMessageUnselectionMethod;
  }

  @Override
  public Symbol getUilFormatSpecification(){
    return uilFormatSpecification;
  }

  @Override
  public Symbol getUilEditStyle(){
    return uilEditStyle;
  }

  @Override
  public String getMessageContents(){
    return messageContents;
  }

  @Override
  public boolean getUilUpdateValue(){
    return uilUpdateValue;
  }

  @Override
  public long getUilTimeStamp(){
    return uilTimeStamp;
  }

  //API
  @Override
  public void uilUpdateText(Object value){
    String stringValue = value.toString();
    if (!stringValue.equals(messageContents)){
      messageContents = stringValue;
      parent.uilUpdateMessageText(this, stringValue);
    }
  }

  @Override
  public void uilCallConcludeMethodForGrobj(UiClientItem win) 
       throws G2AccessException{}
  @Override
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
					    Object actionQueue)  throws G2AccessException{}
  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg,
				      Object buttonOrInitObj, Object actionQueue) throws G2AccessException{}
  @Override
  public Symbol uilGetMessageObjectState(){return null;}

  @Override
  public void uilSelectMessage() throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    parent.uilSelectMessage(this);
  }

  @Override
  public void uilSelectMessageOnWindow(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    parent.uilSelectMessage(this);
  }

  @Override
  public void uilUnselectMessage(){
    parent.uilUnselectMessage(this);
  }

  @Override
  public void uilRemoveMessage(){
    parent.uilRemoveMessage(this);
  }

  @Override
  public void uilRemoveMessageFromList(){
    parent.uilRemoveMessage(this);
  }

  @Override
  public Object getValue(){
    return messageContents;
  }
}
