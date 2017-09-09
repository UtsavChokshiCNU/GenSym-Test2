package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.Button;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Enumeration;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.SymbolArray;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilTextPushbutton;
import com.gensym.classes.modules.uillib.UilIconPushbutton;

public class UilClientPushbuttonImpl extends UilClientButtonImpl
     implements UilClientPushbutton, ActionListener, Serializable{

  static final long serialVersionUID = -980872818615397073L;

  private String label;
  private boolean uilDefaultedButton;
  private boolean uilCancelButton;
  private boolean uilUpdateButton;
  private boolean uilReleaseButtonAfterSelection;
  private boolean uilUpdateValue;

  private UilCallback[] actions;

  public UilClientPushbuttonImpl(UilTextPushbutton uilButton, Button button, Class staticClass) 
       throws G2AccessException{
    super(uilButton, button, staticClass);
    label = (String)uilButton.getLabel();
    uilDefaultedButton = ((Boolean)uilButton.getUilDefaultedButton()).booleanValue();
    uilCancelButton = ((Boolean)uilButton.getUilCancelButton()).booleanValue();
    uilUpdateButton = ((Boolean)uilButton.getUilUpdateButton()).booleanValue();
    uilReleaseButtonAfterSelection = ((Boolean)uilButton.getUilReleaseButtonAfterSelection()).booleanValue();
    setActions((SymbolArray)uilButton.getUilActionDescription(), staticClass);
    init(staticClass);
  }

  public UilClientPushbuttonImpl(UilIconPushbutton uilButton, Button button, Class staticClass) 
       throws G2AccessException{
    super(uilButton, button, staticClass);
    label = (String)uilButton.getLabel();
    uilDefaultedButton = ((Boolean)uilButton.getUilDefaultedButton()).booleanValue();
    uilCancelButton = ((Boolean)uilButton.getUilCancelButton()).booleanValue();
    uilUpdateButton = ((Boolean)uilButton.getUilUpdateButton()).booleanValue();
    uilReleaseButtonAfterSelection = ((Boolean)uilButton.getUilReleaseButtonAfterSelection()).booleanValue();
    uilUpdateValue = ((Boolean)uilButton.getUilUdpateValue()).booleanValue();//Udpate is correct!
    setActions((SymbolArray)uilButton.getUilActionDescription(), staticClass);
    init(staticClass);
  }

  private void init(Class staticClass){
    Symbol callbackName = getCallback();
    if (UilClientConstants.UIL_CONTROL_DIALOG_CALLBACK_.equals(callbackName)){
      setButtonCallback(new UilCallback(callbackName, UilClientConstants.CALLBACK_ARG_TYPES, 
					UilClientConstants.CALLBACK_ARGS));
    }
    else if (UilClientConstants.UIL_DO_NOTHING_.equals(callbackName)){
      setButtonCallback(new UilCallback(callbackName, UilClientConstants.CALLBACK_ARG_TYPES, 
					UilClientConstants.CALLBACK_ARGS));
    }
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(callbackName);
      setButtonCallback(new UilCallback(callbackName, UilClientConstants.CALLBACK_ARG_TYPES, 
					UilClientConstants.CALLBACK_ARGS, 
					staticClass, methodName));
    }

    Button button = (Button)getComponent();
    button.addActionListener(this);
    button.setLabel(label);
  }

  private void setActions(SymbolArray actionArray, Class staticClass) throws G2AccessException{
    Sequence s = actionArray.getG2ArraySequence();
    Enumeration actionList = s.elements();
    actions = new UilCallback[s.size()];
    int i = 0;
    while (actionList.hasMoreElements()){
      Symbol action = (Symbol)actionList.nextElement();
      UilCallback callback;
      if (UILAPI.isDefaultAction(action))
	callback = new UilCallback(action, UilClientConstants.ACTION_ARG_TYPES, 
				   UilClientConstants.ACTION_ARGS);
      else
	callback = new UilCallback(action, UilClientConstants.ACTION_ARG_TYPES, 
				   UilClientConstants.ACTION_ARGS,
				   staticClass,  UilCallback.convertCallbackNameToMethodName(action));
      actions[i++] = callback;
    }
  }

  @Override
  public void actionPerformed(ActionEvent e){
    if (java.beans.Beans.isDesignTime()) return;
    try{
      UilClientDialog dlg = getDialogProxy();
      uilSelectButton((dlg == null ? null : dlg.getWindow()), dlg);
    }
    catch(G2AccessException ex){
      throw new UnexpectedException(ex);
    }
    catch(ClassNotFoundException cnfe){
      throw new UnexpectedException(cnfe);
    }
    catch(InvocationTargetException ite){
      throw new UnexpectedException(ite);
    }
    catch(NoSuchMethodException nsme){
      throw new UnexpectedException(nsme);
    }
    catch(IllegalAccessException iae){
      throw new UnexpectedException(iae);
    }
  }

  //properties
  @Override
  public String getUilLabel(){
    return label;
  }

  @Override
  public void setUilLabel(String label){
    this.label = label;
    ((Button)getComponent()).setLabel(label);
  }

  @Override
  public boolean getUilDefaultedButton(){
    return uilDefaultedButton;
  }

  @Override
  public boolean getUilCancelButton(){
    return uilCancelButton;
  }

  @Override
  public boolean getUilUpdateButton(){
    return uilUpdateButton;
  }

  @Override
  public boolean getUilReleaseButtonAfterSelection(){
    return uilReleaseButtonAfterSelection;
  }

  @Override
  public boolean getUilUpdateValue(){
    return uilUpdateValue;
  }

  //API
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			     Object actionQueue) throws G2AccessException{
    //do nothing
  }
  
  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			       Object actionQueue) throws G2AccessException{
    //do nothing
  }

  @Override
  public void uilAddLabelToButton(String label, Symbol size){
    ((Button)getComponent()).setLabel(label);
  }

  @Override
  public void uilSelectButton(UiClientItem win, UilClientDialog dlg) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{

    UilCallback callback = getButtonCallback();
    Object target = getUilEventTargetObject();
    if (callback == null || callback.isDefaultCallback()){
      if (target instanceof String){
	//  launch subdialog and bind parent/child dialog
	//System.out.println("Launch sub-dialog with id="+target);
	UilDialogManager.uilControlDialogCallback(getDialogProxy().getConnection(), target, null, actions, this);
      }
    }
    else 
      callback.doCallback(new Object[]{this, win, getDialogProxy()});    
    if (UilClientConstants.HOST_DIALOG_.equals(target))
      dlg.uilControlDialogCallback(actions, this, dlg.getWindow());
  }

  @Override
  public UilCallback[] getActions(){
    UilCallback[] copy = new UilCallback[actions.length];
    for (int i=0; i<actions.length; i++)
      copy[i] = actions[i];
    return copy;
  }

}
