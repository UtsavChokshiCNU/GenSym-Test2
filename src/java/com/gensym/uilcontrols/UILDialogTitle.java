package com.gensym.uilcontrols;

import java.awt.Component;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilDialogTitle;

public class UILDialogTitle extends UilClientTextImpl implements UilClientDialogTitle, Serializable{

  static final long serialVersionUID = 7204903125665702804L;

  private Symbol uilJustification;
  private boolean uilTitleButtonBehaviourEnabled;
  private Symbol uilTitleButtonCallback;

  public UILDialogTitle(UilDialogTitle uilTitle, Class staticClass) throws G2AccessException{
    super(uilTitle, null, staticClass);
    uilJustification = (Symbol)uilTitle.getUilJustification();
    uilTitleButtonBehaviourEnabled = ((Boolean)uilTitle.getUilTitleButtonBehaviourEnabled()).booleanValue();
    uilTitleButtonCallback = (Symbol)uilTitle.getUilTitleButtonCallback();
  }

  //properties
  @Override
  public Symbol getUilJustification(){
    return uilJustification;
  }

  @Override
  public boolean getUilTitleButtonBehaviourEnabled(){
    return uilTitleButtonBehaviourEnabled;
  }

  @Override
  public Symbol getUilTitleButtonCallback(){
    return uilTitleButtonCallback;
  }

  //must override all API
  @Override
  public void uilUpdateText(Object value){
    setMessageContents(value.toString());
    UilClientDialog dlg = getDialogProxy();
    if (dlg != null)
      dlg.setTitle(getMessageContents());
  }

  //do nothing:
  @Override
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{}
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException{}
  @Override
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{}
  @Override
  public void uilDisableGrobj(){}
  @Override
  public void uilDisableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{}
  @Override
  public void uilEnableGrobj(){}
  @Override
  public void uilEnableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{}
}
