package com.gensym.uilcontrols;

import java.awt.Component;
import java.io.Serializable;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Date;
import java.io.IOException;
import java.io.EOFException;
import java.lang.reflect.InvocationTargetException;
import com.gensym.controls.FieldType;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.types.G2ParserException;
import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2SyntaxException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.Message;
import com.gensym.classes.VariableOrParameter;
import com.gensym.classes.Parameter;
import com.gensym.classes.G2Variable;
import com.gensym.classes.TextParameter;
import com.gensym.classes.SymbolicParameter;
import com.gensym.classes.LogicalParameter;
import com.gensym.classes.FloatParameter;
import com.gensym.classes.IntegerParameter;
import com.gensym.classes.QuantitativeParameter;
import com.gensym.classes.G2Variable;
import com.gensym.classes.TextVariable;
import com.gensym.classes.SymbolicVariable;
import com.gensym.classes.LogicalVariable;
import com.gensym.classes.FloatVariable;
import com.gensym.classes.IntegerVariable;
import com.gensym.classes.QuantitativeVariable;
import com.gensym.classes.G2Array;
import com.gensym.classes.ValueArray;
import com.gensym.classes.TextArray;
import com.gensym.classes.SymbolArray;
import com.gensym.classes.TruthValueArray;
import com.gensym.classes.FloatArray;
import com.gensym.classes.IntegerArray;
import com.gensym.classes.QuantityArray;
import com.gensym.classes.ItemArray;
import com.gensym.classes.G2List;
import com.gensym.classes.ValueList;
import com.gensym.classes.TextList;
import com.gensym.classes.SymbolList;
import com.gensym.classes.TruthValueList;
import com.gensym.classes.FloatList;
import com.gensym.classes.IntegerList;
import com.gensym.classes.QuantityList;
import com.gensym.classes.ItemList;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.Item;
import com.gensym.classes.modules.uilroot.UilGrobj;
import com.gensym.classes.modules.uilroot.UilGrmes;

abstract class UilClientItemImpl implements UilClientItem, Serializable{

  static final long serialVersionUID = -7567091959272137977L;

  private String id;
  private Object userData;
  private Object uilEventSourceObject;
  private Symbol uilEventSourceAttribute;
  private Object uilEventTargetObject; //Symbol or String
  private Symbol uilEventTargetAttribute;
  private Symbol configuration;
  private Symbol uilSize;
  private boolean uilConcludeValueImmediately;
  private Symbol uilInitializationMethod;
  private Symbol uilSizeOfMethod;
  private Symbol uilConfigurationMethod;
  private Symbol uilCloneMethod;
  private Symbol uilManageMethod;
  private Symbol uilDeleteMethod;

  private Symbol uilEnableMethod;
  private UilCallback enableCallback;
  private Symbol uilDisableMethod;
  private UilCallback disableCallback;
  private Symbol uilUpdateMethod;
  private UilCallback updateCallback;

  private UilClientDialog dialogProxy;

  private Component component;

  public UilClientItemImpl(UilGrobj grobj, Component component, Class staticClass) throws G2AccessException{
    id = (String)grobj.getId();
    userData = grobj.getUserData();
    uilEventSourceObject = grobj.getUilEventSourceObject();
    uilEventSourceAttribute = (Symbol)grobj.getUilEventSourceAttribute();
    uilEventTargetObject = grobj.getUilEventTargetObject();
    uilEventTargetAttribute = (Symbol)grobj.getUilEventTargetAttribute();
    configuration = (Symbol)grobj.getConfiguration();
    uilSize = (Symbol)grobj.getUilSize();
    uilConcludeValueImmediately = ((Boolean)grobj.getUilConcludeValueImmediately()).booleanValue();
    uilInitializationMethod = (Symbol)grobj.getUilInitializationMethod();
    uilSizeOfMethod = (Symbol)grobj.getUilSizeOfMethod();
    uilConfigurationMethod = (Symbol)grobj.getUilConfigurationMethod();
    uilCloneMethod = (Symbol)grobj.getUilCloneMethod();
    uilManageMethod = (Symbol)grobj.getUilManageMethod();
    uilDeleteMethod = (Symbol)grobj.getUilDeleteMethod();
    uilEnableMethod = (Symbol)grobj.getUilEnableMethod();
    uilDisableMethod = (Symbol)grobj.getUilDisableMethod();
    uilUpdateMethod = (Symbol)grobj.getUilUpdateMethod();
    this.component = component;
    init(staticClass);
  }

  public UilClientItemImpl(UilGrmes grmes, Component component, Class staticClass) throws G2AccessException{
    id = (String)grmes.getId();
    userData = grmes.getUserData();
    uilEventSourceObject = grmes.getUilEventSourceObject();
    uilEventSourceAttribute = (Symbol)grmes.getUilEventSourceAttribute();
    uilEventTargetObject = grmes.getUilEventTargetObject();
    uilEventTargetAttribute = (Symbol)grmes.getUilEventTargetAttribute();
    configuration = (Symbol)grmes.getConfiguration();
    uilSize = (Symbol)grmes.getUilSize();
    uilConcludeValueImmediately = ((Boolean)grmes.getUilConcludeValueImmediately()).booleanValue();
    uilInitializationMethod = (Symbol)grmes.getUilInitializationMethod();
    uilSizeOfMethod = (Symbol)grmes.getUilSizeOfMethod();
    uilConfigurationMethod = (Symbol)grmes.getUilConfigurationMethod();
    uilCloneMethod = (Symbol)grmes.getUilCloneMethod();
    uilManageMethod = (Symbol)grmes.getUilManageMethod();
    uilDeleteMethod = (Symbol)grmes.getUilDeleteMethod();
    uilEnableMethod = (Symbol)grmes.getUilEnableMethod();
    uilDisableMethod = (Symbol)grmes.getUilDisableMethod();
    uilUpdateMethod = (Symbol)grmes.getUilUpdateMethod();
    this.component = component;
    init(staticClass);
  }

  private void init(Class staticClass){
    if (UilClientConstants.UIL_UPDATE_GROBJ_METHOD_.equals(uilUpdateMethod))
      setUpdateCallback(new UilCallback(uilUpdateMethod, UilClientConstants.UPDATE_ARG_TYPES, 
					UilClientConstants.UPDATE_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilUpdateMethod);
      setUpdateCallback(new UilCallback(uilUpdateMethod, UilClientConstants.UPDATE_ARG_TYPES, 
					UilClientConstants.UPDATE_ARGS, staticClass, 
					methodName));
    }

    if (UilClientConstants.UIL_ENABLE_GROBJ_METHOD_.equals(uilEnableMethod))
      setEnableCallback(new UilCallback(uilEnableMethod, UilClientConstants.ENABLE_ARG_TYPES, 
					UilClientConstants.ENABLE_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilEnableMethod);
      setEnableCallback(new UilCallback(uilEnableMethod, UilClientConstants.ENABLE_ARG_TYPES,
					UilClientConstants.ENABLE_ARGS, staticClass, 
					methodName));
    }

    if (UilClientConstants.UIL_DISABLE_GROBJ_METHOD_.equals(uilDisableMethod))
      setDisableCallback(new UilCallback(uilDisableMethod, UilClientConstants.DISABLE_ARG_TYPES, 
					 UilClientConstants.DISABLE_ARGS));
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilDisableMethod);
      setDisableCallback(new UilCallback(uilDisableMethod, UilClientConstants.DISABLE_ARG_TYPES, 
					 UilClientConstants.DISABLE_ARGS, staticClass, 
					 methodName));
    }
  }

  protected UilClientItemImpl(){
  }

  protected Component getComponent(){
    return component;
  }

  @Override
  public String getId(){
    return id;
  }

  @Override
  public Object getUserData(){
    return userData;
  }

  @Override
  public void setUserData(Object data){
    userData = data;
  }

  @Override
  public Object getUilEventSourceObject(){
    return uilEventSourceObject; 
  }

  @Override
  public Symbol getUilEventSourceAttribute(){
    return uilEventSourceAttribute;
  }

  @Override
  public Object getUilEventTargetObject(){
    return uilEventTargetObject;
  }

  @Override
  public Symbol getUilEventTargetAttribute(){
    return uilEventTargetAttribute;
  }
  
  @Override
  public Symbol getConfiguration(){
    return configuration;
  }

  @Override
  public Symbol getUilSize(){
    return uilSize;
  }

  @Override
  public boolean getUilConcludeValueImmediately(){
    return uilConcludeValueImmediately;
  }

  @Override
  public Symbol getUilInitializationMethod(){
    return uilInitializationMethod;
  }

  @Override
  public Symbol getUilEnableMethod(){
    return uilEnableMethod;
  }

  @Override
  public Symbol getUilDisableMethod(){
    return uilDisableMethod;
  }

  @Override
  public Symbol getUilSizeOfMethod(){
    return uilSizeOfMethod;
  }

  @Override
  public Symbol getUilConfigurationMethod(){
    return uilConfigurationMethod;
  }

  @Override
  public Symbol getUilCloneMethod(){
    return uilCloneMethod;
  }

  @Override
  public Symbol getUilManageMethod(){
    return uilManageMethod;
  }

  @Override
  public Symbol getUilUpdateMethod(){
    return uilUpdateMethod;
  }

  @Override
  public Symbol getUilDeleteMethod(){
    return uilDeleteMethod;
  }

  @Override
  public UilCallback getUpdateCallback(){
    return updateCallback;
  }

  @Override
  public void setUpdateCallback(UilCallback callback){
    updateCallback = callback;
  }

  @Override
  public UilCallback getEnableCallback(){
    return enableCallback;
  }

  @Override
  public void setEnableCallback(UilCallback callback){
    enableCallback = callback;
  }

  @Override
  public UilCallback getDisableCallback(){
    return disableCallback;
  }

  @Override
  public void setDisableCallback(UilCallback callback){
    this.disableCallback = callback;
  }

  //API
  @Override
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilUpdateGrobjMethod(win, getDialogProxy(), null, null);
  }

  @Override
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
   if (updateCallback == null || updateCallback.isDefaultCallback())
     uilUpdateGrobj(win, dlg, button, actionQueue);
    else
      updateCallback.doCallback(new Object[]{this, win, dlg, button, actionQueue});

  }

  @Override
  public void uilDisableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
   if (disableCallback == null || disableCallback.isDefaultCallback())
      uilDisableGrobj();
    else
      disableCallback.doCallback(new Object[]{this});
  }

  @Override
  public void uilDisableGrobj(){
    component.setEnabled(false);
  }

  @Override
  public void uilEnableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
   if (enableCallback == null || enableCallback.isDefaultCallback())
      uilEnableGrobj();
    else
      enableCallback.doCallback(new Object[]{this});
  }

  @Override
  public void uilEnableGrobj(){
    component.setEnabled(true);
  }

  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException{
   uppConcludeValueToTarget();
  }

  protected void uppConcludeValueToTarget() throws G2AccessException{
    Item targetObject = getTargetObject();
    //System.out.println("uilConcludeGrobj: targetObject="+targetObject);
    if (targetObject == null) return;
    Object value = null;
    Symbol targetAttributeName = getUilEventTargetAttribute();
    //System.out.println("targetAttributeName="+targetAttributeName);
    if (targetAttributeName != null && !targetAttributeName.equals(UilClientConstants.UNSPECIFIED_)){
      try{
	Object currentValue = targetObject.getPropertyValue(targetAttributeName);
	//System.out.println("currentValue="+currentValue);
	value = getValue();
	//System.out.println("value="+value);
	if (isValue(currentValue))
	  uppConcludeValueToAttribute(targetObject, targetAttributeName, value);
	else
	  uppConcludeValueToItem(currentValue, value);
      }
      catch(NoSuchAttributeException ex){
	uppConcludeValueToItem(targetObject, value);
      }
    }
  }

  @Override
  public void setDialogProxy(UilClientDialog dlg){
    dialogProxy = dlg;
  }

  @Override
  public UilClientDialog getDialogProxy(){
    return dialogProxy;
  }

  //misc support
  protected Object uppExtractValue(Object object) throws G2AccessException{
    if (isValue(object))
      return object;
    else
      return uppExtractValueFromItem(object);
  }

  protected boolean isValue(Object value){
    return (value instanceof Symbol || value instanceof String || value instanceof Number || 
	    value instanceof Boolean || value == null);
  }

  private static final Symbol DATA_POINT_VALUE_ = Symbol.intern("DATA-POINT-VALUE");

  protected Object uppExtractValueFromItem(Object item) throws G2AccessException{
    if (item instanceof Message)
      return ((Message)item).getText();
    else if (item instanceof Parameter || item instanceof G2Variable){
      Structure valueStructure = ((VariableOrParameter)item).getValueStructure();
      return valueStructure.getAttributeValue(DATA_POINT_VALUE_, null);
    }
    else if (item instanceof G2List)
      return getValueFromSequence(((G2List)item).getG2ListSequence());
    else if (item instanceof G2Array)
      return getValueFromSequence(((G2Array)item).getG2ArraySequence());
    else return null;
  }

  private Object getValueFromSequence(Sequence list) throws G2AccessException{
    int size = list.size();
    if (size > 0){
      Object object = list.elementAt(size - 1);
      if (isValue(object))
	return object;
      else
	return uppExtractValueFromItem(object);
    }
    else 
      return null;
  }

  protected Sequence getValuesFromSequence(Sequence list) throws G2AccessException{
    Sequence values = null;
    Enumeration valueList = list.elements();
    while (valueList.hasMoreElements()){
      Object object = valueList.nextElement();
      if (isValue(object)){
	if (values == null) values = new Sequence();
	values.addElement(object);
      }
      else{
	Object value = uppExtractValueFromItem(object);
	if (value != null){
	  if (values == null) values = new Sequence();
	  values.addElement(value);
	}
      }
    }
    return values;
  }

  protected void concludeSequenceToAttribute(Item item, Symbol targetAtt, Sequence values) 
       throws G2AccessException{
     if (item instanceof G2Array && targetAtt.equals("INITIAL-VALUES")){
       if (item instanceof ItemArray)
	 concludeValuesToItemListOrItemArray(item, values.size());
       else if (item instanceof ValueArray)
	 concludeSequenceToValueListOrValueArray(item, values);
     }
     else if (values.size() > 0)
       uppConcludeValueToAttribute(item, targetAtt, values.elementAt(values.size() - 1));
  }
  
  protected void uppConcludeValueToAttribute(Item item, Symbol targetAtt, Object value)
       throws G2AccessException{
    //System.out.println("uppConcludeValueToAttribute:"+item+" "+targetAtt+" "+value);
    if (item instanceof G2Array && targetAtt.equals("INITIAL-VALUES"))
      uppConcludeValueToItem(item, value);
    else
      item.setPropertyValue(targetAtt, value);
  }

  protected void uppConcludeValueToItem(Object item, Object value)
       throws G2AccessException{
    //System.out.println("uppConcludeValueToItem:"+item+" "+value);
    if (item instanceof G2Array || item instanceof G2List){
      if (item instanceof ItemArray || item instanceof ItemList)
	concludeValuesToItemListOrItemArray(item, 1);
      else if (item instanceof ValueArray || item instanceof ValueList)
	concludeValuesToValueListOrValueArray(item, new String[]{value.toString()});
    }
    else if (item instanceof Parameter || item instanceof G2Variable)
      concludeValueToParameterOrVariable((VariableOrParameter)item, value.toString());
    else if (item instanceof Message){
      ((Message)item).setText(value.toString());
    }
  }

  protected void concludeSequenceToItem(Object item, Sequence values) throws G2AccessException{
    if (item instanceof ValueList || item instanceof G2Array)
      concludeSequenceToValueListOrValueArray(item, values);
    else if (values.size() > 0){
      if (item instanceof G2Variable || item instanceof Parameter)
	concludeValueToParameterOrVariable((VariableOrParameter)item, values.elementAt(0).toString());
      else if (item instanceof Message)
	((Message)item).setText(values.elementAt(0).toString());
    }
  }

  private static final Symbol DATA_POINT_COLLECTION_TIME_ = Symbol.intern("DATA-POINT-COLLECTION-TIME");
  private static final Symbol DATA_POINT_EXPIRATION_TIME_ = Symbol.intern("DATA-POINT-EXPIRATION-TIME");
  private static final Symbol NEVER_ = Symbol.intern("NEVER");

  protected static final String TEXT = "Text";
  protected static final String SYMBOL = "Symbol";
  protected static final String TRUTH_VALUE = "BooleanTruthValue";
  protected static final String FLOAT = "Float";
  protected static final String INTEGER = "Integer";
  protected static final String QUANTITY = "Quantity";

  protected void concludeValueToParameterOrVariable(VariableOrParameter item, String stringValue)
       throws G2AccessException{
    //System.out.println("concludeValueToParameterOrVariable");
    Object value = null;
    FieldType fieldType = null;
    if (item instanceof TextParameter || item instanceof TextVariable)
      value = stringValue;
    else if (item instanceof SymbolicParameter || item instanceof SymbolicVariable)
      fieldType = new FieldType(SYMBOL);
    else if (item instanceof LogicalParameter || item instanceof LogicalVariable)
      fieldType = new FieldType(TRUTH_VALUE);
    else if (item instanceof FloatParameter || item instanceof FloatVariable)
      fieldType = new FieldType(FLOAT);
    else if (item instanceof IntegerParameter || item instanceof IntegerVariable)
      fieldType = new FieldType(INTEGER);
    else if (item instanceof QuantitativeParameter || item instanceof QuantitativeVariable)
      fieldType = new FieldType(QUANTITY);
    
    if (value == null){
      try{
	value = fieldType.stringToObject(stringValue);
      }
      catch(G2TokenizerException gte){}
      catch(G2ParserException gpe){}
      catch(EOFException eof){}
      catch(IOException ioe){}
    }
       
    if (value != null){
      Structure structValue = new Structure();
      structValue.setAttributeValue(DATA_POINT_VALUE_, value);
      //structValue.setAttributeValue(DATA_POINT_COLLECTION_TIME_, new Long(new Date().getTime()));
      //structValue.setAttributeValue(DATA_POINT_EXPIRATION_TIME_, NEVER_);
      //System.out.println("structValue="+structValue);
      item.setValueStructure(structValue);
    }
  }

  //what about length==0 for array?
  protected void concludeValuesToValueListOrValueArray(Object item, String[] values) throws G2AccessException{
    //System.out.println("concludeValuesToValueListOrValueArray: values.length="+values.length);
    FieldType fieldType = null;
    if (item instanceof TextList || item instanceof TextArray){}
    else if (item instanceof SymbolList || item instanceof SymbolArray)
      fieldType = new FieldType(SYMBOL);
    else if (item instanceof TruthValueList || item instanceof TruthValueArray)
      fieldType = new FieldType(TRUTH_VALUE);
    else if (item instanceof FloatList || item instanceof FloatArray)
      fieldType = new FieldType(FLOAT);
    else if (item instanceof IntegerList || item instanceof IntegerArray)
      fieldType = new FieldType(INTEGER);
    else if (item instanceof QuantityList || item instanceof QuantityArray)
      fieldType = new FieldType(QUANTITY);
    else return;

    Sequence list = new Sequence();
    for (int i=0; i<values.length; i++){
      if (fieldType == null)
	list.addElement(values[i]);
      else{
	try{
	  Object value = fieldType.stringToObject(values[i]);
	  list.addElement(value);
	}
	catch(G2TokenizerException gte){}
	catch(G2ParserException gpe){}
	catch(EOFException eof){}
	catch(IOException ioe){}
      }
    }

    concludeSequenceToValueListOrValueArray(item, list);
  }
    
  private void concludeSequenceToValueListOrValueArray(Object item, Sequence list) throws G2AccessException{
    //System.out.println("concludeSequenceToValueListOrValueArray");
    if (item instanceof G2List)
      ((G2List)item).setG2ListSequence(list);
    else{
      G2Array array = (G2Array)item;
      array.setG2ArraySequence(list);
      if (list.size() == 0){
	if (item instanceof TextArray)
	  list.addElement("");
	else if (item instanceof SymbolArray)
	  list.addElement(Symbol.intern("G2"));
	else if (item instanceof TruthValueArray)
	  list.addElement(Boolean.FALSE);
	else if (item instanceof FloatArray)
	  list.addElement(new Float(0.0));
	else if (item instanceof IntegerArray)
	  list.addElement(new Integer(0));
	else if (item instanceof QuantityArray)
	  list.addElement(new Double(0.0));
      }
      array.setInitialValues(list);
    }
  }

  private void concludeValuesToItemListOrItemArray(Object item, int length) throws G2AccessException{
    Symbol elementType;
    if (item instanceof ItemArray)
      elementType = ((ItemArray)item).getElementType();
    else
      elementType = ((ItemList)item).getElementType();
    Sequence list = new Sequence();
    G2Access connection = ((ImplAccess)item).getContext();
    for (int i=0; i<length; i++)
      list.addElement(connection.createItem(elementType));
    
    if (item instanceof ItemList)
      ((ItemList)item).setG2ListSequence(list);
    else{
      ItemArray array = (ItemArray)item;
      array.setG2ArraySequence(list);
      array.setInitialValues(list);
    }
  }

  private static final Symbol INITIATING_OBJECT_ = Symbol.intern("INITIATING-OBJECT");
  
  //only supports init-object
  protected Item getSourceObject(){
    Object uilSourceObj = getUilEventSourceObject();
    if (uilSourceObj instanceof Symbol){
      Symbol sourceObj = (Symbol)uilSourceObj;
      if (sourceObj.equals(INITIATING_OBJECT_)){
	if (dialogProxy != null && dialogProxy.getProxy() != null)
	  return dialogProxy.getProxy().getProxy();
      }
    } 
    return null;
  }

  //only support init-object
  protected Item getTargetObject(){
    Object uilTargetObj = getUilEventTargetObject();
    if (uilTargetObj instanceof Symbol){
      Symbol targetObj = (Symbol)uilTargetObj;
      if (targetObj.equals(INITIATING_OBJECT_)){
	if (dialogProxy != null && dialogProxy.getProxy() != null)
	  return dialogProxy.getProxy().getProxy();
      }
    } 
    return null;
  }

  public Object getValue(){
    return null;
  }
  public Sequence getValues(){
    return null;
  }
}
