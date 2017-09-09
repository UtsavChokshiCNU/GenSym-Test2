package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.TextField;
import java.awt.event.FocusListener;
import java.awt.event.FocusEvent;
import java.io.Serializable;
import java.io.IOException;
import java.io.EOFException;
import java.lang.reflect.InvocationTargetException;
import com.gensym.dlg.WarningDialog;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.widgets.TextWidget;
import com.gensym.types.G2SyntaxException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.ItemArray;
import com.gensym.classes.G2Array;
import com.gensym.classes.ItemList;
import com.gensym.classes.G2List;
import com.gensym.classes.ValueArray;
import com.gensym.classes.ValueList;
import com.gensym.classes.Parameter;
import com.gensym.classes.G2Variable;
import com.gensym.classes.VariableOrParameter;
import com.gensym.classes.Message;
import com.gensym.classes.modules.uillib.UilEditBox;

class UilClientEditBoxImpl extends UilClientGrmesImpl implements UilClientEditBox, FocusListener, 
	     Serializable{

  static final long serialVersionUID = 1855014230481944771L;

  private Symbol uilEditStyle;
  private boolean uilAllowFieldEditOfThisMessage;
  private Symbol uilFormatSpecification;
  private boolean uilClearTextBeforeEdit;
  private Symbol uilConcludeMethod;
  private boolean uilValidateValueImmediately;
  private Symbol uilValidationMethod;
  private Symbol uilMessageSelectionMethod;
  private Symbol uilMessageUnselectionMethod;
  private String label;
  private Symbol state;
  private String messageContents;
  private boolean uilUpdateValue;
  private Boolean uilUseGrammarPerTargetSpecifications;

  private UilCallback concludeCallback;
  private UilCallback validateCallback;
  private UilCallback selectionCallback;
  private UilCallback unselectionCallback;

  private TextWidget labelComponent;

  protected UILFormatSpec fieldType;

  UilClientEditBoxImpl(UilEditBox uilEditBox, TextField textField, 
		       Class staticClass) throws G2AccessException{
    super(uilEditBox, textField, staticClass);
    uilEditStyle = (Symbol)uilEditBox.getUilEditStyle(); 
    uilAllowFieldEditOfThisMessage = ((Boolean)uilEditBox.getUilAllowFieldEditOfThisMessage()).booleanValue();
    uilFormatSpecification = (Symbol)uilEditBox.getUilFormatSpecification();
    uilClearTextBeforeEdit = ((Boolean)uilEditBox.getUilClearTextBeforeEdit()).booleanValue();
    uilConcludeMethod = (Symbol)uilEditBox.getUilConcludeMethod(); 
    uilValidateValueImmediately = ((Boolean)uilEditBox.getUilValidateValueImmediately()).booleanValue();
    uilValidationMethod = (Symbol)uilEditBox.getUilValidationMethod(); 
    uilMessageSelectionMethod = (Symbol)uilEditBox.getUilMessageSelectionMethod();
    uilMessageUnselectionMethod = (Symbol)uilEditBox.getUilMessageUnselectionMethod();
    label = (String)uilEditBox.getLabel();
    state = (Symbol)uilEditBox.getState();
    messageContents = (String)uilEditBox.getMessageContents();
    uilUpdateValue = ((Boolean)uilEditBox.getUilUpdateValue()).booleanValue();
    uilUseGrammarPerTargetSpecifications = (Boolean)uilEditBox.getUilUseGrammarPerTargetSpecifications();

    G2Access connection = ((ImplAccess)uilEditBox).getContext();//is this kosher?
    fieldType = UILFormatSpec.create(connection, uilFormatSpecification);

    textField.addFocusListener(this);
    //textField.setEditable(false);

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
    if (UilClientConstants.UIL_CONCLUDE_GROBJ_METHOD_.equals(uilConcludeMethod))
      setConcludeCallback(new UilCallback(uilConcludeMethod, UilClientConstants.CONCLUDE_ARG_TYPES, 
					  UilClientConstants.CONCLUDE_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilConcludeMethod);
      setConcludeCallback(new UilCallback(uilConcludeMethod, UilClientConstants.CONCLUDE_ARG_TYPES, 
					  UilClientConstants.CONCLUDE_ARGS,
					  staticClass, methodName));
    }
    if (UilClientConstants.UIL_EDIT_BOX_SELECTION_METHOD_.equals(uilMessageSelectionMethod))
      setMessageSelectionCallback(new UilCallback(uilMessageSelectionMethod, 
						  UilClientConstants.EDIT_BOX_SELECTION_ARG_TYPES, 
						  UilClientConstants.EDIT_BOX_SELECTION_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilMessageSelectionMethod);
      setMessageSelectionCallback(new UilCallback(uilMessageSelectionMethod, 
						  UilClientConstants.EDIT_BOX_SELECTION_ARG_TYPES, 
						  UilClientConstants.EDIT_BOX_SELECTION_ARGS,
						  staticClass, methodName));
    }
    if (UilClientConstants.UIL_EDIT_BOX_UNSELECTION_METHOD_.equals(uilMessageUnselectionMethod))
      setMessageUnselectionCallback(new UilCallback(uilMessageUnselectionMethod, 
						    UilClientConstants.EDIT_BOX_UNSELECTION_ARG_TYPES, 
						    UilClientConstants.EDIT_BOX_UNSELECTION_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilMessageUnselectionMethod);
      setMessageUnselectionCallback(new UilCallback(uilMessageUnselectionMethod,
						    UilClientConstants.EDIT_BOX_UNSELECTION_ARG_TYPES, 
						    UilClientConstants.EDIT_BOX_UNSELECTION_ARGS, 
						    staticClass, methodName));
    }
  }

  @Override
  public void focusGained(FocusEvent event){
    try{
      UilClientDialog dlg = getDialogProxy();
      if (dlg != null){
	uilEditBoxSelectionMethod(dlg, dlg.getWindow());
	TextField textField = (TextField)getComponent();
	textField.setCaretPosition(textField.getText().length());
      }
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

  @Override
  public void focusLost(FocusEvent event){
    UilClientDialog dlg = getDialogProxy();
    try {
      if (dlg != null)
	uilEditBoxUnselectionMethod(dlg, dlg.getWindow(), Boolean.TRUE);
    } catch(ClassNotFoundException cnfe){
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
  public Symbol getUilEditStyle(){
    return uilEditStyle;
  }

  @Override
  public boolean getUilAllowFieldEditOfThisMessage(){
    return uilAllowFieldEditOfThisMessage;
  }

  @Override
  public Symbol getUilFormatSpecification(){
    return uilFormatSpecification;
  }

  @Override
  public boolean getUilClearTextBeforeEdit(){
    return uilClearTextBeforeEdit;
  }

  @Override
  public Symbol getUilConcludeMethod(){
    return uilConcludeMethod;
  }

  @Override
  public boolean getUilValidateValueImmediately(){
    return uilValidateValueImmediately;
  }

  @Override
  public Symbol getUilValidationMethod(){
    return uilValidationMethod;
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
  public String getLabel(){
    return label;
  }

  @Override
  public void setLabel(String label){
    this.label = label;
    if (labelComponent != null)
      labelComponent.setText(label);
    else
      throw new IllegalStateException("This edit-box does not have a labelComponent");
  }

  @Override
  public Symbol getUilState(){
    return state;
  }

  @Override
  public String getMessageContents(){
    return messageContents;
  }

  @Override
  public void setMessageContents(String txt){
    messageContents = txt;
  }

  @Override
  public boolean getUilUpdateValue(){
    return uilUpdateValue;
  }

  @Override
  public Boolean getUilUseGrammarPerTargetSpecifications(){
    return uilUseGrammarPerTargetSpecifications;
  }

  //callbacks
  @Override
  public UilCallback getConcludeCallback(){
    return concludeCallback;
  }

  @Override
  public void setConcludeCallback(UilCallback callback){
    concludeCallback = callback;
  }

  @Override
  public UilCallback getValidationCallback(){
    return validateCallback;
  }

  @Override
  public void setValidationCallback(UilCallback callback){
    validateCallback = callback;
  }

  @Override
  public UilCallback getMessageSelectionCallback(){
    return selectionCallback;
  }

  @Override
  public void setMessageSelectionCallback(UilCallback callback){
    selectionCallback = callback;
  }

  @Override
  public UilCallback getMessageUnselectionCallback(){
    return unselectionCallback;
  }

  @Override
  public void setMessageUnselectionCallback(UilCallback callback){
    unselectionCallback = callback;
  }

  //API
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException{
    if (uilUpdateValue)
      super.uilUpdateGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

  @Override
  public void uilUpdateText(Object value){
    if (!fieldType.isFormatTypeSpecified())
      fieldType.setFormatTypeForValue(value);
    uilUpdateText0(value, true);
  }

  private void uilUpdateText0(Object value, boolean addQuotes){
    String txt = fieldType.objectToString(value);
    if (addQuotes && fieldType.isText() && !fieldType.getManageQuotes()) 
      txt = "\""+txt+"\"";
    messageContents = txt;
    clipText(txt);
  }

  @Override
  public String uilCallValidateMethodForGrobj(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilValidateGrobjMethod(win, null, null, null);
  }

  @Override
  public String uilValidateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				       Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (validateCallback == null || validateCallback.isDefaultCallback())
      return uilValidateGrobj(win, dlg, button, actionQueue);
    else
      return (String)validateCallback.doCallback(new Object[]{this, win, dlg, button, actionQueue});
  }

  @Override
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object button, Object actionQueue){
    String result = fieldType.validate(((TextField)getComponent()).getText(), getUilEventTargetAttribute());
    return result;
  }

  @Override
  public void uilCallConcludeMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilConcludeGrobjMethod(win, null, null, null);
  }

  @Override
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button,
				     Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (concludeCallback == null || concludeCallback.isDefaultCallback())
      uilConcludeGrobj(win, dlg, button, actionQueue);
    else
      concludeCallback.doCallback(new Object[]{this, win, dlg, button, actionQueue});
  }

  @Override
  public Object uilGetEditBoxValue(){
    return messageContents;
  }

  @Override
  public void uilUpdateEditBoxLabel(){
    //to do
    //System.out.println("Not yet implemented.");
  }

  @Override
  public void uilEditBoxSelectionMethod(UilClientDialog dlg, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (selectionCallback == null || selectionCallback.isDefaultCallback())
      uilEditBoxSelection(dlg, win);
    else
      selectionCallback.doCallback(new Object[]{this, dlg, win});
  }

  @Override
  public void uilEditBoxSelection(UilClientDialog dlg, UiClientItem win){
    //System.out.println("uilClientEditBoxImpl.uilEditBoxSelection: uilClearTextBeforeExit="+uilClearTextBeforeEdit);
    //((TextField)getComponent()).setEditable(true);
    if (uilClearTextBeforeEdit)
      ((TextField)getComponent()).setText("");
    else
      ((TextField)getComponent()).setText(messageContents);
  }

  @Override
  public void uilEditBoxUnselectionMethod(UilClientDialog dlg, UiClientItem win, Boolean committed) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (unselectionCallback == null || unselectionCallback.isDefaultCallback())
      uilEditBoxUnselection(dlg, win, committed);
    else
      unselectionCallback.doCallback(new Object[]{this, dlg, win, committed});
  }

  @Override
  public void uilEditBoxUnselection(UilClientDialog dlg, UiClientItem win, Boolean committed) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    //System.out.println("uilClientEditBoxImpl.uilEditBoxUnselection: committed="+committed);
    if (!committed.booleanValue()) return;
    String previousMessageContents = messageContents;
    String text = ((TextField)getComponent()).getText();
    uilUpdateText0(text, false);
    boolean validationFailed = false;
    //System.out.println("uilValidateValueImmediately="+uilValidateValueImmediately);
    if (uilValidateValueImmediately){
      String result = uilValidateGrobjMethod(win, dlg, null, null);
      if (!result.toLowerCase().equals(UILFormatSpec.OK)){
	validationFailed = true;
	//if validation-failure-method of formatSpec exists - > use it else post default dlg
	postValidationError(result);
	if (fieldType.getUilRevertValueOnError())
	  uilUpdateText0(previousMessageContents, false);
      }
    }
    
    if (!validationFailed){
      //System.out.println("uilConcludeValueImmediately="+getUilConcludeValueImmediately());
      if (getUilConcludeValueImmediately() && dlg != null && !java.beans.Beans.isDesignTime()){
	try{
	  uilCallConcludeMethodForGrobj(dlg.getWindow());
	}
	catch(G2AccessException ex){
	  throw new UnexpectedException(ex);
	}
      }
    }
    //((TextField)getComponent()).setEditable(false);
  }

  private void postValidationError(String message){
    new WarningDialog(null, "", true, message, null).setVisible(true);
  }

  @Override
  public void uilSelectEditBox(UilClientDialog dlg, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilEditBoxSelectionMethod(dlg, win);
  }

  @Override
  public void uilSelectEditBoxOnDialog(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilEditBoxSelectionMethod(getDialogProxy(), win);
  }

  //misc
  @Override
  public Object getValue(){
    try{
      return fieldType.stringToObject(messageContents);
    }
    catch (G2SyntaxException syntaxException){
      throw new UnexpectedException(syntaxException);
    }
    catch (EOFException eof){
      throw new UnexpectedException(eof);
    }
    catch (IOException e){
      throw new UnexpectedException(e);
    } 
  }

  @Override
  public void setLabelComponent(TextWidget text){
    labelComponent = text;
    label = (text == null ? null : text.getText());
  }

  @Override
  public TextWidget getLabelComponent(){
    return labelComponent;
  }

  @Override
  public void uilDisableGrobj(){
    super.uilDisableGrobj();
    if (labelComponent != null && labelComponent instanceof Component)
      ((Component)labelComponent).setEnabled(false);
  }

  @Override
  public void uilEnableGrobj(){
    super.uilEnableGrobj();
    if (labelComponent != null && labelComponent instanceof Component)
      ((Component)labelComponent).setEnabled(true);
  }

}
