package com.gensym.uilcontrols;

import java.awt.Component;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilGrobj;

abstract class UilClientGrobjImpl extends UilClientItemImpl implements UilClientGrobj, Serializable{

  static final long serialVersionUID = -1782494248238796969L;

  private Symbol uilValidationMethod;
  private UilCallback validationCallback;
  private Symbol uilConcludeMethod;
  private UilCallback concludeCallback;

  public UilClientGrobjImpl(UilGrobj grobj, Component component, Class staticClass) throws G2AccessException{
    super(grobj, component, staticClass);
    uilValidationMethod = (Symbol)grobj.getUilValidationMethod();
    uilConcludeMethod = (Symbol)grobj.getUilConcludeMethod();
    init(staticClass);
  }

  private void init(Class staticClass){
    if (UilClientConstants.UIL_VALIDATE_GROBJ_METHOD_.equals(uilValidationMethod))
      setValidationCallback(new UilCallback(uilValidationMethod, UilClientConstants.VALIDATION_ARG_TYPES, 
					    UilClientConstants.VALIDATION_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilValidationMethod);
      setValidationCallback(new UilCallback(uilValidationMethod, UilClientConstants.VALIDATION_ARG_TYPES, 
					    UilClientConstants.VALIDATION_ARGS,
					    staticClass, methodName));
    }

    if (UilClientConstants.NONE_.equals(uilConcludeMethod))
      setConcludeCallback(null);
    else if (UilClientConstants.UIL_CONCLUDE_GROBJ_METHOD_.equals(uilConcludeMethod))
      setConcludeCallback(new UilCallback(uilConcludeMethod, UilClientConstants.CONCLUDE_ARG_TYPES, 
					  UilClientConstants.CONCLUDE_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilConcludeMethod);
      setConcludeCallback(new UilCallback(uilConcludeMethod, UilClientConstants.CONCLUDE_ARG_TYPES, 
					  UilClientConstants.CONCLUDE_ARGS,
					  staticClass, methodName));
    }
  }

  //properties
  @Override
  public Symbol getUilValidationMethod(){
    return uilValidationMethod;
  }

  @Override
  public UilCallback getValidationCallback(){
    return validationCallback;
  }

  @Override
  public void setValidationCallback(UilCallback callback){
    validationCallback = callback;
  }

  @Override
  public Symbol getUilConcludeMethod(){
    return uilConcludeMethod;
  }

  @Override
  public UilCallback getConcludeCallback(){
    return concludeCallback;
  }

  @Override
  public void setConcludeCallback(UilCallback callback){
    concludeCallback = callback;
  }

  //API
  @Override
  public String uilCallValidateMethodForGrobj(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilValidateGrobjMethod(win, getDialogProxy(), null, null);
  }

  @Override
  public String uilValidateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				       Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
   if (validationCallback == null || validationCallback.isDefaultCallback())
      return uilValidateGrobj(win, dlg, button, actionQueue);
    else
      return (String)validationCallback.doCallback(new Object[]{this, win, dlg, button, actionQueue});
  }

  @Override
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
				 Object actionQueue){
    return UilClientConstants.OK;
  }

  @Override
  public void uilCallConcludeMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilConcludeGrobjMethod(win, getDialogProxy(), null, null);
  }

  @Override
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				     Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
   if (concludeCallback == null || concludeCallback.isDefaultCallback())
      uilConcludeGrobj(win, dlg, button, actionQueue);
    else
      concludeCallback.doCallback(new Object[]{this, win, dlg, button, actionQueue});
  }

}




