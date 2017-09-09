//synch
//display msg list

package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.List;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.lang.reflect.InvocationTargetException;
import java.io.Serializable;
import java.io.IOException;
import java.io.EOFException;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Date;
import com.gensym.controls.FieldType;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.types.G2ParserException;
import com.gensym.types.G2TokenizerException;
import com.gensym.types.G2SyntaxException;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.Item;
import com.gensym.classes.G2Array;
import com.gensym.classes.ValueArray;
import com.gensym.classes.ItemArray;
import com.gensym.classes.ItemList;
import com.gensym.classes.G2List;
import com.gensym.classes.ValueList;
import com.gensym.classes.Message;
import com.gensym.classes.Parameter;
import com.gensym.classes.G2Variable;
import com.gensym.classes.VariableOrParameter;
import com.gensym.classes.modules.uilsa.UilScrollArea;
import com.gensym.classes.modules.uilsa.UilMessageObject;

class UilClientScrollAreaImpl extends UilClientGrobjImpl implements UilClientScrollArea, ItemListener, 
	     Serializable{

  static final long serialVersionUID = -3364052617008673670L;

  private static final double DEFAULT_PRIORITY = 0.0;
  
  private static final Symbol PRIORITY_ = Symbol.intern("PRIORITY");
  private static final Symbol LOGBOOK_ = Symbol.intern("LOGBOOK");
  private static final Symbol CHRONOLOGICAL_ = Symbol.intern("CHRONOLOGICAL");
  private static final Symbol ALPHABETIC_ = Symbol.intern("ALPHABETIC");
  private static final Symbol UNORDERED_ = Symbol.intern("UNORDERED");

  private static final Symbol CLEAR_AND_INSERT_ = Symbol.intern("CLEAR-AND-INSERT");
  private static final Symbol SELECT_MATCHING_VALUES_ = Symbol.intern("SELECT-MATCHING-VALUES");
  private static final Symbol REUSE_MESSAGES_ = Symbol.intern("REUSE-MESSAGES");

  private static final Symbol CONCLUDE_SELECTED_ = Symbol.intern("CONCLUDE-SELECTED");
  private static final Symbol CONCLUDE_ALL_ = Symbol.intern("CONCLUDE-ALL");

  private Symbol orderingMethod;
  private int maximumAllowedMessages;
  private Symbol uilMessageSelectionMethod;
  private Symbol uilMessageUnselectionMethod;
  private Symbol uilScrollIncrementMethod;
  private Symbol uilScrollDecrementMethod;
  private Symbol uilScrollIncrementLineMethod;
  private Symbol uilScrollDecrementLineMethod;
  private Symbol uilScrollToPositionMethod;
  private boolean allowMultipleSimultaneousSelections;
  private boolean allowUnselectOnSelectedMessage;
  private Symbol uilUpdateStyle;
  private Symbol uilConcludeStyle;
  private Object uilMaximumCharactersToDisplay;
  private boolean uilAllowManualMessageMove;
  private Symbol uilFormatSpecification;
  private boolean uilDisplayDisabledMessages;
  private boolean uilUpdateValue;

  private UilCallback selectionCallback;
  private UilCallback unselectionCallback;

  private Vector messages;
  private Vector extraMessages;

  private UILFormatSpec fieldType;

  public UilClientScrollAreaImpl(UilScrollArea uilScrollArea, List component, Class staticClass) 
       throws G2AccessException{
    super(uilScrollArea, component, staticClass);
    orderingMethod = (Symbol)uilScrollArea.getOrderingMethod();
    maximumAllowedMessages = ((Integer)uilScrollArea.getMaximumAllowedMessages()).intValue();
    uilMessageSelectionMethod = (Symbol)uilScrollArea.getUilMessageSelectionMethod();
    uilMessageUnselectionMethod = (Symbol)uilScrollArea.getUilMessageUnselectionMethod();
    uilScrollIncrementMethod = (Symbol)uilScrollArea.getUilScrollIncrementMethod();
    uilScrollDecrementMethod = (Symbol)uilScrollArea.getUilScrollDecrementMethod();
    uilScrollIncrementLineMethod = (Symbol)uilScrollArea.getUilScrollIncrementLineMethod();
    uilScrollDecrementLineMethod = (Symbol)uilScrollArea.getUilScrollDecrementLineMethod();
    uilScrollToPositionMethod =(Symbol) uilScrollArea.getUilScrollToPositionMethod();
    allowMultipleSimultaneousSelections = ((Boolean)uilScrollArea.getAllowMultipleSimultaneousSelections()).booleanValue();
    allowUnselectOnSelectedMessage = ((Boolean)uilScrollArea.getAllowUnselectOnSelectedMessage()).booleanValue();
    uilUpdateStyle = (Symbol)uilScrollArea.getUilUpdateStyle();
    uilConcludeStyle = (Symbol)uilScrollArea.getUilConcludeStyle();
    Object uilMaximumCharactersToDisplay = uilScrollArea.getUilMaximumCharactersToDisplay();
    uilAllowManualMessageMove = ((Boolean)uilScrollArea.getUilAllowManualMessageMove()).booleanValue();
    uilFormatSpecification = (Symbol)uilScrollArea.getUilFormatSpecification();
    uilDisplayDisabledMessages = ((Boolean)uilScrollArea.getUilDisplayDisabledMessages()).booleanValue();
    uilUpdateValue = ((Boolean)uilScrollArea.getUilUpdateValue()).booleanValue();

    messages = new Vector();
    extraMessages = new Vector();
    component.setMultipleMode(allowMultipleSimultaneousSelections);

    ItemList msgList = (ItemList)uilScrollArea.getMessageList();
    Enumeration msgs = msgList.getG2ListSequence().elements();
    while (msgs.hasMoreElements()){
      UilMessageObject uilMsgObject = (UilMessageObject)msgs.nextElement();
      UILMessageObject msgObject = new UILMessageObject(this, uilMsgObject, staticClass);
      uilAddMessageToList(msgObject);
    }

    G2Access connection = ((ImplAccess)uilScrollArea).getContext();//is this kosher?
    fieldType = UILFormatSpec.create(connection, uilFormatSpecification);
    
    component.addItemListener(this);
    init(staticClass);
  }
  
  private void init(Class staticClass){
    if (uilMessageSelectionMethod.equals(UilClientConstants.UIL_MESSAGE_SELECTION_METHOD_))
      selectionCallback = new UilCallback(uilMessageSelectionMethod, UilClientConstants.SELECTION_ARG_TYPES, 
					  UilClientConstants.SELECTION_ARGS);
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilMessageSelectionMethod);
      selectionCallback = new UilCallback(uilMessageSelectionMethod, UilClientConstants.SELECTION_ARG_TYPES, 
					  UilClientConstants.SELECTION_ARGS,
					  staticClass, methodName);
    }

    if (uilMessageUnselectionMethod.equals(UilClientConstants.UIL_MESSAGE_UNSELECTION_METHOD_))
      unselectionCallback = new UilCallback(uilMessageUnselectionMethod, 
					    UilClientConstants.SELECTION_ARG_TYPES, 
					    UilClientConstants.SELECTION_ARGS);
    else{
      String methodName = UilCallback.convertCallbackNameToMethodName(uilMessageUnselectionMethod);
      unselectionCallback = new UilCallback(uilMessageUnselectionMethod, 
					    UilClientConstants.SELECTION_ARG_TYPES, 
					    UilClientConstants.SELECTION_ARGS,
					    staticClass, methodName);
    }
  }

  @Override
  public void itemStateChanged(ItemEvent event){
    if (java.beans.Beans.isDesignTime()) return;
    List list = (List)getComponent();
    int index = ((Integer)event.getItem()).intValue();
    try{     
      if (event.getStateChange() == event.SELECTED){
	list.deselect(index);
	uilMessageSelectionMethod((UilClientMessageObject)messages.elementAt(index), 
				  getDialogProxy().getWindow());
      }
      else{
	list.select(index);
	uilMessageSelectionMethod((UilClientMessageObject)messages.elementAt(index),
				    getDialogProxy().getWindow());
      }
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
  public Symbol getOrderingMethod(){
    return orderingMethod;
  }

  @Override
  public int getMaximumAllowedMessages(){
    return maximumAllowedMessages;
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
  public Symbol getUilScrollIncrementMethod(){
    return uilScrollIncrementMethod;
  }

  @Override
  public Symbol getUilScrollDecrementMethod(){
    return uilScrollDecrementMethod;
  }

  @Override
  public Symbol getUilScrollIncrementLineMethod(){
    return uilScrollIncrementLineMethod;
  }

  @Override
  public Symbol getUilScrollDecrementLineMethod(){
    return uilScrollDecrementLineMethod;
  }

  @Override
  public Symbol getUilScrollToPositionMethod(){
    return uilScrollToPositionMethod;
  }

  @Override
  public boolean getAllowMultipleSimultaneousSelections(){
    return allowMultipleSimultaneousSelections;
  }

  @Override
  public boolean getAllowUnselectOnSelectedMessage(){
    return allowUnselectOnSelectedMessage;
  }

  @Override
  public Symbol getUilUpdateStyle(){
    return uilUpdateStyle;
  }

  @Override
  public Symbol getUilConcludeStyle(){
    return uilConcludeStyle;
  }

  @Override
  public Object getUilMaximumCharactersToDisplay(){
    return uilMaximumCharactersToDisplay;
  }

  @Override
  public boolean getUilAllowManualMessageMove(){
    return uilAllowManualMessageMove;
  }

  @Override
  public Symbol getUilFormatSpecification(){
    return uilFormatSpecification;
  }

  @Override
  public boolean getUilDisplayDisabledMessages(){
    return uilDisplayDisabledMessages;
  }

  @Override
  public boolean getUilUpdateValue(){
    return uilUpdateValue;
  }

  //callbacks
  @Override
  public UilCallback getUilMessageSelectionCallback(){
    return selectionCallback;
  }

  @Override
  public void setUilMessageSelectionCallback(UilCallback callback){
    selectionCallback = callback;
  }

  @Override
  public UilCallback getUilMessageUnselectionCallback(){
    return unselectionCallback;
  }

  @Override
  public void setUilMessageUnselectionCallback(UilCallback callback){
    unselectionCallback = callback;
  }

  //API  
  @Override
  public UilClientMessageObject uilCreateMessageObject(Object value, double priority){
    UilClientMessageObject newMsg = new UILMessageObject(this, value, priority);
    uilAddMessageToList(newMsg);
    return newMsg;
  }

  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException{
    if (!uilUpdateValue) return;
    Item sourceObject = getSourceObject();
    if (sourceObject == null) return;
    try{
      Object value = null;
      Symbol sourceAttributeName = getUilEventSourceAttribute();
      if (sourceAttributeName != null && !sourceAttributeName.equals(UilClientConstants.UNSPECIFIED_))
	value = sourceObject.getPropertyValue(sourceAttributeName);
      else
	value = sourceObject;
      if (value != null){
	Sequence list = uppExtractValues(value);
	if (list != null)
	  updateFromSequence(list);
	else if (uilUpdateStyle.equals(CLEAR_AND_INSERT_))
	  uilClearMessages();
      }
      else{
	if (uilUpdateStyle.equals(CLEAR_AND_INSERT_))
	  uilClearMessages();
      }
    }
    catch(NoSuchAttributeException ex){
      if (uilUpdateStyle.equals(CLEAR_AND_INSERT_))
	uilClearMessages();
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
	       
  private Sequence uppExtractValues(Object value) throws G2AccessException{
    if (isValue(value)){
      Sequence list = new Sequence();
      list.addElement(value);
      return list;
    }
    else
      return uppExtractValuesFromItem(value);
  }

  private Sequence uppExtractValuesFromItem(Object item) throws G2AccessException{
    if (item instanceof ValueList)
      return ((ValueList)item).getG2ListSequence();
    else if (item instanceof ValueArray)
      return((ValueArray)item).getG2ArraySequence();
    else if (item instanceof G2Array)
      return getValuesFromSequence(((G2Array)item).getG2ArraySequence());
    else if (item instanceof G2List){
      return getValuesFromSequence(((G2List)item).getG2ListSequence());
    }
    else{
      Object value = uppExtractValueFromItem(item);
      if (value != null){
	Sequence list = new Sequence();
	list.addElement(value);
	return list;
      }
      else
	return null;
    }
  }

  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException{
    Item targetObject = getTargetObject();
    if (targetObject == null) return;

    Symbol targetAttributeName = getUilEventTargetAttribute();
    if ((targetAttributeName == null || targetAttributeName.equals(UilClientConstants.UNSPECIFIED_)) &&
	(!(targetObject instanceof G2Array || targetObject instanceof G2List || 
	   targetObject instanceof G2Variable || targetObject instanceof Parameter))) 
      return;
      
      if (targetAttributeName != null && !targetAttributeName.equals(UilClientConstants.UNSPECIFIED_)){
	Object currentValue;
	try{
	  currentValue = targetObject.getPropertyValue(targetAttributeName);
	  if (isValue(currentValue))
	    uppConcludeScrollAreaToScalar(targetObject, targetAttributeName);
	  else
	    concludeToItem(currentValue);
	}
	catch(NoSuchAttributeException ex){
	  concludeToItem(targetObject);
	}
      }
      else
	concludeToItem(targetObject);
  }

  private void uppConcludeScrollAreaToScalar(Item item, Symbol attributeName) throws G2AccessException{
    //assume selected messages and conclude last selection
    List list = (List)getComponent();
    String[] items = list.getSelectedItems();
    if (items.length > 0){
      String stringValue = items[items.length - 1];
      try{
	Object value = fieldType.stringToObject(stringValue);
	item.setPropertyValue(attributeName, value);
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
  }

  private void concludeToItem(Object item) throws G2AccessException{
    if (item instanceof ItemList || item instanceof ItemArray)
      return;
    else if (item instanceof G2List || item instanceof G2Array){
      if ((item instanceof ValueList) || (item instanceof ValueArray)){
	List list = (List)getComponent();
	String[] values;
	if (uilConcludeStyle.equals(CONCLUDE_SELECTED_))
	  values = list.getSelectedItems();
	else
	  values = list.getItems();
	concludeValuesToValueListOrValueArray(item, values);
      }
    }
    else if (item instanceof Parameter || item instanceof G2Variable){
      //assume selected messages and conclude last item selection
      List list = (List)getComponent();
      String[] items = list.getSelectedItems();
      String stringValue = items[items.length - 1];
      concludeValueToParameterOrVariable((VariableOrParameter)item, stringValue);
    }
  }

  @Override
  public void uilRemoveMessage(UilClientMessageObject msgObject){
    int index = messages.indexOf(msgObject);
    if (index > 0)
      removeMessage(index);
  }

  private void removeMessage(int index){
    ((List)getComponent()).remove(index);
    messages.removeElementAt(index);
  }

  @Override
  public void uilClearMessages(){
    messages.removeAllElements();
    ((List)getComponent()).removeAll();
  }

  @Override
  public void uilDeleteSelectedMessages(){
    UilClientMessageObject[] msgs = getSelectedMessageObjects();
    if (msgs != null){
      List list = (List)getComponent();
      for (int i=0; i<msgs.length; i++){
	int index = messages.indexOf(msgs[i]);
	removeMessage(index);
      }
    }
  }

  private UilClientMessageObject[] getSelectedMessageObjects(){
    List list = (List)getComponent();
    int[] selection = list.getSelectedIndexes();
    if (selection != null){
      UilClientMessageObject[] msgs = new UilClientMessageObject[selection.length];
      for (int i=0; i<selection.length; i++)
	msgs[i] = (UilClientMessageObject)messages.elementAt(selection[i]);
      return msgs;
    }
    else return null;
  }

  private Sequence getSelectedMessageObjectsAsSequence(){
    List list = (List)getComponent();
    int[] selection = list.getSelectedIndexes();
    Sequence msgs = new Sequence();
    if (selection != null){
      for (int i=0; i<selection.length; i++)
	msgs.addElement(messages.elementAt(selection[i]));
    }
    return msgs;
  }

  @Override
  public void uilDisplayMessageList(int index){
    ((List)getComponent()).makeVisible(index);//this isn't quite right
  }

  @Override
  public int uilGetIndexOfScrollMessage(UilClientMessageObject msgObject){
    return messages.indexOf(msgObject);
  }

  @Override
  public UilClientMessageObject uilGetMessageFromIndex(int index){
    if (index < messages.size())
      return (UilClientMessageObject)messages.elementAt(index);
    else
      throw new IllegalArgumentException("index "+index+" is out of bounds");
  }

  @Override
  public void uilMessageSelectionMethod(UilClientMessageObject msgObject, UiClientItem win)
       throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    if (selectionCallback == null || selectionCallback.isDefaultCallback())
      uilMessageSelection(msgObject, win);
    else
      selectionCallback.doCallback(new Object[]{msgObject, this, win});
  }

  @Override
  public void uilMessageSelection(UilClientMessageObject msgObject, UiClientItem win) 
       throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    UilClientMessageObject[] msgs = getSelectedMessageObjects();
    boolean selected = false;
    if (msgs != null){
      for (int i=0; i<msgs.length; i++){
	//System.out.println("equal?"+msgs[i].getMessageContents());
	if (msgObject.equals(msgs[i])){
	  selected = true;
	  break;
	}
      }
    }

    if (selected && allowUnselectOnSelectedMessage)
      uilMessageUnselectionMethod(msgObject, win);
    else
      uilSelectMessage(msgObject);
  }

  @Override
  public void uilMessageUnselectionMethod(UilClientMessageObject msgObject, UiClientItem win)
       throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    if (unselectionCallback == null || unselectionCallback.isDefaultCallback())
      uilMessageUnselection(msgObject, win);
    else
      unselectionCallback.doCallback(new Object[]{msgObject, this, win});
  }

  @Override
  public void uilMessageUnselection(UilClientMessageObject msgObject,  UiClientItem win){
    uilUnselectMessage(msgObject);
  }

  @Override
  public void uilSelectMessage(UilClientMessageObject msgObject) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    int index = messages.indexOf(msgObject);
    if (index >= 0)
      ((List)getComponent()).select(index);
    if (getUilConcludeValueImmediately())
      uilCallConcludeMethodForGrobj(getDialogProxy().getWindow());
  }

  @Override
  public void uilUnselectMessage(UilClientMessageObject msgObject){
    int index = messages.indexOf(msgObject);
    //System.out.println("uilUnselectMessage:"+index);
    if (index >= 0)
      ((List)getComponent()).deselect(index);
  }

  @Override
  public void uilResetScrollArea(){
    UilClientMessageObject[] msgs = getSelectedMessageObjects();
    if (msgs != null){
      for (int i=0; i<msgs.length; i++)
	uilUnselectMessage(msgs[i]);
    }
    uilDisplayMessageList(0);
  }

  private static final Symbol MESSAGE_ADDED_TO_LIST_ = Symbol.intern("MESSAGE-ADDED-TO-LIST");
  private static final Symbol MESSAGE_NOT_ADDED_TO_LIST_ = Symbol.intern("MESSAGE-NOT-ADDED-TO-LIST");

  @Override
  public Symbol uilAddMessageToList(UilClientMessageObject msgObject){
    if (messages.contains(msgObject)) return MESSAGE_ADDED_TO_LIST_;
    int position;
    if (orderingMethod.equals(ALPHABETIC_))
      position = addMessageToAlphabeticSortedList(msgObject);
    else if (orderingMethod.equals(PRIORITY_))
      position = addMessageToPrioritySortedList(msgObject);
    else if (orderingMethod.equals(CHRONOLOGICAL_))
      position = addMessageToChronologicalSortedList(msgObject);
    else if (orderingMethod.equals(LOGBOOK_))
      position = addMessageToLogbookSortedList(msgObject);
    else 
      position = addMessageToUnsortedList(msgObject);

    insertMessage(msgObject, position);

    int size = messages.size();
    if (size > maximumAllowedMessages){
      UilClientMessageObject msgObjectToRemove;
      if (orderingMethod.equals(CHRONOLOGICAL_))
	msgObjectToRemove = (UilClientMessageObject)messages.elementAt(0);
      else
	msgObjectToRemove = (UilClientMessageObject)messages.elementAt(size - 1);
      uilRemoveMessage(msgObjectToRemove);
      if (msgObjectToRemove.equals(msgObject))
	return MESSAGE_NOT_ADDED_TO_LIST_;
      else
	return MESSAGE_ADDED_TO_LIST_;
    }
    else
      return MESSAGE_ADDED_TO_LIST_;
  }

  private int addMessageToAlphabeticSortedList(UilClientMessageObject msgObject){
    int index = -1;
    for (int i=0; i<messages.size(); i++){
      UilClientMessageObject msg = (UilClientMessageObject)messages.elementAt(i);
      if (msg.getMessageContents().compareTo(msgObject.getMessageContents()) >= 0){
	index = i;
	break;
      }
    }
    return index;
  }

  private int addMessageToPrioritySortedList(UilClientMessageObject msgObject){
    int index = -1;
    for (int i=0; i<messages.size(); i++){
      UilClientMessageObject msg = (UilClientMessageObject)messages.elementAt(i);
      if (msg.getMessageDisplayPriority() >= msgObject.getMessageDisplayPriority()){
	index = i;
	break;
      }
    }
    return index;
  }

  private int addMessageToChronologicalSortedList(UilClientMessageObject msgObject){
    int index = -1;
    for (int i=0; i<messages.size(); i++){
      UilClientMessageObject msg = (UilClientMessageObject)messages.elementAt(i);
      if (msg.getUilTimeStamp() >= msgObject.getUilTimeStamp())
	index = i;
      else
	break;
    }
    return index;
  }

  private int addMessageToLogbookSortedList(UilClientMessageObject msgObject){
    int index = -1;
    for (int i=0; i<messages.size(); i++){
      UilClientMessageObject msg = (UilClientMessageObject)messages.elementAt(i);
      if (msg.getUilTimeStamp() <= msgObject.getUilTimeStamp()){
	index = i;
	break;
      }
    }
    return index;
  }

  private int addMessageToUnsortedList(UilClientMessageObject msgObject){
    return -1;
  }

  private void insertMessage(UilClientMessageObject msgObject, int index){
    List list = (List)getComponent();
    if (index == -1){
      messages.addElement(msgObject);
      list.add(msgObject.getMessageContents());
    }
    else{
      messages.insertElementAt(msgObject, index);
      list.add(msgObject.getMessageContents(), index);
    }
  }

  @Override
  public void uilUpdateScrollAreaFromList(G2List list) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    Sequence values = uppExtractValuesFromItem(list);
    if (values != null)
      updateFromSequence(values);
  }

  @Override
  public void uilUpdateScrollAreaFromArray(G2Array array) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    Sequence values = uppExtractValuesFromItem(array);
    if (values != null)
      updateFromSequence(values);
  }

  @Override
  public void updateFromSequence(Sequence valueList)  throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    List list = (List)getComponent();
    if (uilUpdateStyle.equals(CLEAR_AND_INSERT_)){
      uilClearMessages();
      Enumeration values = valueList.elements();
      while (values.hasMoreElements()){
	//format?
	String msg = values.nextElement().toString();
	uilCreateMessageObject(msg, DEFAULT_PRIORITY);
      }
    }
    else if (uilUpdateStyle.equals(SELECT_MATCHING_VALUES_)){
      Enumeration values = valueList.elements();
      while (values.hasMoreElements()){
	String msg = values.nextElement().toString();
	Enumeration msgs = messages.elements();
	while (msgs.hasMoreElements()){
	  UilClientMessageObject msgObject = (UilClientMessageObject)msgs.nextElement();
	  if (msg.equals(msgObject.getMessageContents()))
	    uilSelectMessage(msgObject);
	}
      }
    }
    else if (uilUpdateStyle.equals(REUSE_MESSAGES_)){
      if (valueList.size() > (messages.size() + extraMessages.size()))
	throw new IllegalStateException("The number of items to update exceeds the number of messages managed ny the scroll area.  Update can not continue.");
      else{
	Enumeration values = valueList.elements();
	int i = 0;	
	while (values.hasMoreElements()){
	  Object value = values.nextElement();
	  UilClientMessageObject msgObject;
	  if (i < messages.size()){
	    msgObject = (UilClientMessageObject)messages.elementAt(i);
	    msgObject.uilUpdateText(value);
	    ((List)getComponent()).replaceItem(msgObject.getMessageContents(), i++);
	  }
	  else{
	    msgObject = (UilClientMessageObject)extraMessages.elementAt(0);
	    extraMessages.removeElementAt(0);
	    insertMessage(msgObject, -1);
	  }
	}
	for (i=messages.size()-1; i>=valueList.size();  i--){
	  extraMessages.addElement(messages.elementAt(i));
	  messages.removeElementAt(i);
	  list.remove(i);
	}
      }
    }
    uilDisplayMessageList(0);
  }

  @Override
  public String[] uilGetSelectedMessage(){
    List list = (List)getComponent();
    return list.getSelectedItems();
  }

  @Override
  public UilClientMessageObject[] uilGetSelectedMessageObjects(){
    return getSelectedMessageObjects();
  }

  //misc
  @Override
  public Object getValue(){
    if (allowMultipleSimultaneousSelections)
      return null;
    else
      return getSelectedMessageObjectsAsSequence();
  }

  @Override
  public Sequence getValues(){
    if (allowMultipleSimultaneousSelections)
      return getSelectedMessageObjectsAsSequence();
    else
      return null;
  }

  @Override
  public String[] getMessages(){
    return ((List)getComponent()).getItems();
  }

  @Override
  public UilClientMessageObject[] getMessageObjects(){
    UilClientMessageObject[] msgs = new UilClientMessageObject[messages.size()];
    messages.copyInto(msgs);
    return msgs;
  }

  @Override
  public void uilUpdateMessageText(UilClientMessageObject msgObject, String text){
    if (extraMessages.contains(msgObject)){
      msgObject.uilUpdateText(text);
    }
    else if (messages.contains(msgObject)){
      msgObject.uilUpdateText(text);
      int index = messages.indexOf(msgObject);
      ((List)getComponent()).replaceItem(text, index);    
    }
  }
}
