package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.List;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.G2Array;
import com.gensym.classes.G2List;
import com.gensym.classes.modules.uilsa.UilScrollArea;

public class UILScrollArea extends List implements UilClientScrollArea{

  static final long serialVersionUID = -1584979542939564743L;

  private UilClientScrollArea uilHelper;

  public UILScrollArea(UilScrollArea uilScrollArea, Class staticClass) throws G2AccessException{
    uilHelper = new UilClientScrollAreaImpl(uilScrollArea, this, staticClass);
  }

  //UilClientScrollArea interface
  //properties
  @Override
  public String getId(){
    return uilHelper.getId();
  }
  @Override
  public Object getUserData(){
    return uilHelper.getUserData();
  }
  @Override
  public void setUserData(Object data){
    uilHelper.setUserData(data);
  }
  @Override
  public Object getUilEventSourceObject(){
    return uilHelper.getUilEventSourceObject();
  }
  @Override
  public Symbol getUilEventSourceAttribute(){
    return uilHelper.getUilEventSourceAttribute();
  }
  @Override
  public Object getUilEventTargetObject(){
    return uilHelper.getUilEventTargetObject();
  }
  @Override
  public Symbol getUilEventTargetAttribute(){
    return uilHelper.getUilEventTargetAttribute();
  }
  @Override
  public Symbol getConfiguration(){
    return uilHelper.getConfiguration();
  }
  @Override
  public Symbol getUilSize(){
    return uilHelper.getUilSize();
  }
  @Override
  public boolean getUilConcludeValueImmediately(){
    return uilHelper.getUilConcludeValueImmediately();
  }
  @Override
  public Symbol getUilInitializationMethod(){
    return uilHelper.getUilInitializationMethod();
  }
  @Override
  public Symbol getUilEnableMethod(){
    return uilHelper.getUilEnableMethod();
  }
  @Override
  public Symbol getUilDisableMethod(){
    return uilHelper.getUilDisableMethod();
  }
  @Override
  public Symbol getUilSizeOfMethod(){
    return uilHelper.getUilSizeOfMethod();
  }
  @Override
  public Symbol getUilConfigurationMethod(){
    return uilHelper.getUilConfigurationMethod();
  }
  @Override
  public Symbol getUilCloneMethod(){
    return uilHelper.getUilCloneMethod();
  }
  @Override
  public Symbol getUilManageMethod(){
    return uilHelper.getUilManageMethod();
  }
  @Override
  public Symbol getUilUpdateMethod(){
    return uilHelper.getUilUpdateMethod();
  }
  @Override
  public Symbol getUilDeleteMethod(){
    return uilHelper.getUilDeleteMethod();
  }
  @Override
  public UilCallback getUpdateCallback(){
    return uilHelper.getUpdateCallback();
  }
  @Override
  public void setUpdateCallback(UilCallback callback){
    uilHelper.setUpdateCallback(callback);
  }
  @Override
  public UilCallback getEnableCallback(){
    return uilHelper.getEnableCallback();
  }
  @Override
  public void setEnableCallback(UilCallback callback){
    uilHelper.setEnableCallback(callback);
  }
  @Override
  public UilCallback getDisableCallback(){
    return uilHelper.getDisableCallback();
  }
  @Override
  public void setDisableCallback(UilCallback callback){
    uilHelper.setDisableCallback(callback);
  }
  @Override
  public Symbol getUilValidationMethod(){
    return uilHelper.getUilValidationMethod();
  }
  @Override
  public UilCallback getValidationCallback(){
    return uilHelper.getValidationCallback();
  }
  @Override
  public void setValidationCallback(UilCallback callback){
    uilHelper.setValidationCallback(callback);
  }
  @Override
  public Symbol getUilConcludeMethod(){
    return uilHelper.getUilConcludeMethod();
  }
  @Override
  public UilCallback getConcludeCallback(){
    return uilHelper.getConcludeCallback();
  }
  @Override
  public void setConcludeCallback(UilCallback callback){
    uilHelper.setConcludeCallback(callback);
  }
  @Override
  public Symbol getOrderingMethod(){
    return uilHelper.getOrderingMethod();
  }
  @Override
  public int getMaximumAllowedMessages(){
    return uilHelper.getMaximumAllowedMessages();
  }
  @Override
  public Symbol getUilMessageSelectionMethod(){
    return uilHelper.getUilMessageSelectionMethod();
  }
  @Override
  public Symbol getUilMessageUnselectionMethod(){
    return uilHelper.getUilMessageUnselectionMethod();
  }
  @Override
  public Symbol getUilScrollIncrementMethod(){
    return uilHelper.getUilScrollIncrementMethod();
  }
  @Override
  public Symbol getUilScrollDecrementMethod(){
    return uilHelper.getUilScrollDecrementMethod();
  }
  @Override
  public Symbol getUilScrollIncrementLineMethod(){
    return uilHelper.getUilScrollIncrementLineMethod();
  }
  @Override
  public Symbol getUilScrollDecrementLineMethod(){
    return uilHelper.getUilScrollDecrementLineMethod();
  }
  @Override
  public Symbol getUilScrollToPositionMethod(){
    return uilHelper.getUilScrollToPositionMethod();
  }
  @Override
  public boolean getAllowMultipleSimultaneousSelections(){
    return uilHelper.getAllowMultipleSimultaneousSelections();
  }
  @Override
  public boolean getAllowUnselectOnSelectedMessage(){
    return uilHelper.getAllowUnselectOnSelectedMessage();
  }
  @Override
  public Symbol getUilUpdateStyle(){
    return uilHelper.getUilUpdateStyle();
  }
  @Override
  public Symbol getUilConcludeStyle(){
    return uilHelper.getUilConcludeStyle();
  }
  @Override
  public Object getUilMaximumCharactersToDisplay(){
    return uilHelper.getUilMaximumCharactersToDisplay();
  }
  @Override
  public boolean getUilAllowManualMessageMove(){
    return uilHelper.getUilAllowManualMessageMove();
  }
  @Override
  public Symbol getUilFormatSpecification(){
    return uilHelper.getUilFormatSpecification();
  }
  @Override
  public boolean getUilDisplayDisabledMessages(){
    return uilHelper.getUilDisplayDisabledMessages();
  }
  @Override
  public boolean getUilUpdateValue(){
    return uilHelper.getUilUpdateValue();
  }
  //callbacks
  @Override
  public UilCallback getUilMessageSelectionCallback(){
    return uilHelper.getUilMessageSelectionCallback();
  }
  @Override
  public void setUilMessageSelectionCallback(UilCallback callback){
    uilHelper.setUilMessageSelectionCallback(callback);
  }
  @Override
  public UilCallback getUilMessageUnselectionCallback(){
    return uilHelper.getUilMessageUnselectionCallback();
  }
  @Override
  public void setUilMessageUnselectionCallback(UilCallback callback){
    uilHelper.setUilMessageUnselectionCallback(callback);
  }
  //API
  @Override
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallUpdateMethodForGrobj(win);
  }
  @Override
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilUpdateGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			     Object actionQueue) throws G2AccessException{
    uilHelper.uilUpdateGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public void uilDisableGrobjMethod()throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilDisableGrobjMethod();
  }
  @Override
  public void uilDisableGrobj(){
    uilHelper.uilDisableGrobj();
  }
  @Override
  public void uilEnableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilEnableGrobjMethod();
  }
  @Override
  public void uilEnableGrobj(){
    uilHelper.uilEnableGrobj();
  }
  @Override
  public void setDialogProxy(UilClientDialog dlg){
    uilHelper.setDialogProxy(dlg);
  }
  @Override
  public UilClientDialog getDialogProxy(){
    return uilHelper.getDialogProxy();
  }
  @Override
  public String uilCallValidateMethodForGrobj(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilHelper.uilCallValidateMethodForGrobj(win);
  }
  @Override
  public String uilValidateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
					 Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilHelper.uilValidateGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
				 Object actionQueue){
    return uilHelper.uilValidateGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public void uilCallConcludeMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallConcludeMethodForGrobj(win);
  }
  @Override
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				     Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilConcludeGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			       Object actionQueue) throws G2AccessException{
    uilHelper.uilConcludeGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public UilClientMessageObject uilCreateMessageObject(Object value, double priority){
    return uilHelper.uilCreateMessageObject(value, priority);
  }
  @Override
  public void uilClearMessages(){
    uilHelper.uilClearMessages();
  }
  @Override
  public void uilDeleteSelectedMessages(){
    uilHelper.uilDeleteSelectedMessages();
  }
  @Override
  public void uilRemoveMessage(UilClientMessageObject msgObject){
    uilHelper.uilRemoveMessage(msgObject);
  }
  @Override
  public void uilDisplayMessageList(int index){
    uilHelper.uilDisplayMessageList(index);
  }
  @Override
  public int uilGetIndexOfScrollMessage(UilClientMessageObject msgObject){ 
    return uilHelper.uilGetIndexOfScrollMessage(msgObject);
  }
  @Override
  public UilClientMessageObject uilGetMessageFromIndex(int index){ 
    return uilHelper.uilGetMessageFromIndex(index);
  }
  @Override
  public void uilSelectMessage(UilClientMessageObject msgObject) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    uilHelper.uilSelectMessage(msgObject);
  }
  @Override
  public void uilUnselectMessage(UilClientMessageObject msgObject){
    uilHelper.uilUnselectMessage(msgObject);
  }
  @Override
  public void uilMessageSelectionMethod(UilClientMessageObject msgObject, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    uilHelper.uilMessageSelectionMethod(msgObject, win);
  }
  @Override
  public void uilMessageSelection(UilClientMessageObject msgObject, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    uilHelper.uilMessageSelection(msgObject, win);
  }
  @Override
  public void uilMessageUnselectionMethod(UilClientMessageObject msgObject, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    uilHelper.uilMessageUnselectionMethod(msgObject, win);
  }
  @Override
  public void uilMessageUnselection(UilClientMessageObject msgObject,  UiClientItem win){
    uilHelper.uilMessageUnselection(msgObject, win);
  }
  @Override
  public void uilResetScrollArea(){
    uilHelper.uilResetScrollArea();
  }
  @Override
  public Symbol uilAddMessageToList(UilClientMessageObject msgObject){
    return uilHelper.uilAddMessageToList(msgObject);
  }
  @Override
  public void uilUpdateScrollAreaFromList(G2List list) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    uilHelper.uilUpdateScrollAreaFromList(list);
  }
  @Override
  public void uilUpdateScrollAreaFromArray(G2Array array) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
    uilHelper.uilUpdateScrollAreaFromArray(array);
  }
  @Override
  public String[] uilGetSelectedMessage(){
    return uilHelper.uilGetSelectedMessage();
  }
  @Override
  public UilClientMessageObject[] uilGetSelectedMessageObjects(){
    return uilHelper.uilGetSelectedMessageObjects();
  }
  @Override
  public String[] getMessages(){
    return uilHelper.getMessages();
  }
  @Override
  public void updateFromSequence(Sequence list)throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.updateFromSequence(list);
  }
  @Override
  public UilClientMessageObject[] getMessageObjects(){
    return uilHelper.getMessageObjects();
  }
  @Override
  public void uilUpdateMessageText(UilClientMessageObject msgObject, String text){
   uilHelper.uilUpdateMessageText(msgObject, text);
  }
}
