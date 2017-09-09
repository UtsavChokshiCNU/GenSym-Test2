package com.gensym.uilcontrols;

import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Item;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.G2List;
import com.gensym.classes.G2Array;

public class UILAPI{

  //grobj and grmes
  public static void uilCallUpdateMethodForGrobj(UilClientItem grobj, UiClientItem win) 
       throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    grobj.uilCallUpdateMethodForGrobj(win);
  }

  public static void uilUpdateGrobj(UilClientItem grobj, UiClientItem win, UilClientDialog dlg,
				    Object buttonOrInitObj, Object actionQueue) throws G2AccessException{
    grobj.uilUpdateGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

  public static void uilUpdateGrobjMethod(UilClientItem grobj, UiClientItem win, UilClientDialog dlg,
				      Item buttonOrInitObj, Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    grobj.uilUpdateGrobjMethod(win, dlg, buttonOrInitObj, actionQueue);
  }

  public static void uilCallConcludeMethodForGrobj(UilClientItem grobj, UiClientItem win) 
       throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (grobj instanceof UilClientGrobj)
      ((UilClientGrobj)grobj).uilCallConcludeMethodForGrobj(win);
    else if (grobj instanceof UilClientEditBox)
      ((UilClientEditBox)grobj).uilCallConcludeMethodForGrobj(win);
    else if (grobj instanceof UilClientMessageObject)
      ((UilClientMessageObject)grobj).uilCallConcludeMethodForGrobj(win);
  }

  public static void uilConcludeGrobj(UilClientItem grobj, UiClientItem win, UilClientDialog dlg,
				      Object buttonOrInitObj, Object actionQueue) throws G2AccessException{
    if (grobj instanceof UilClientGrobj)
      ((UilClientGrobj)grobj).uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
    else if (grobj instanceof UilClientEditBox)
      ((UilClientEditBox)grobj).uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
    else if (grobj instanceof UilClientMessageObject)
      ((UilClientMessageObject)grobj).uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

  public static void uilConcludeGrobjMethod(UilClientItem grobj, UiClientItem win, UilClientDialog dlg,
				      Object buttonOrInitObj, Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (grobj instanceof UilClientGrobj)
      ((UilClientGrobj)grobj).uilConcludeGrobjMethod(win, dlg, buttonOrInitObj, actionQueue);
    else if (grobj instanceof UilClientEditBox)
      ((UilClientEditBox)grobj).uilConcludeGrobjMethod(win, dlg, buttonOrInitObj, actionQueue);
    else if (grobj instanceof UilClientMessageObject)
      ((UilClientMessageObject)grobj).uilConcludeGrobjMethod(win, dlg, buttonOrInitObj, actionQueue);
  }

  public static String uilValidateGrobj(UilClientItem grobj, UiClientItem win, UilClientDialog dlg, 
					Object buttonOrInitObj, Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (grobj instanceof UilClientGrobj)
      return ((UilClientGrobj)grobj).uilValidateGrobj(win, dlg, buttonOrInitObj, actionQueue);
    else if (grobj instanceof UilClientEditBox)
      return ((UilClientEditBox)grobj).uilValidateGrobj(win, dlg, buttonOrInitObj, actionQueue);
    else throw new IllegalArgumentException("Expected either a UilClientGrobj or UilClientEditBox");
  }

  public static String uilValidateGrobjMethod(UilClientItem grobj, UiClientItem win, UilClientDialog dlg, 
					Object buttonOrInitObj, Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (grobj instanceof UilClientGrobj)
      return ((UilClientGrobj)grobj).uilValidateGrobjMethod(win, dlg, buttonOrInitObj, actionQueue);
    else if (grobj instanceof UilClientEditBox)
      return ((UilClientEditBox)grobj).uilValidateGrobjMethod(win, dlg, buttonOrInitObj, actionQueue);
    else throw new IllegalArgumentException("Expected either a UilClientGrobj or UilClientEditBox");
  }

  public static String uilCallValidateMethodForGrobj(UilClientItem grobj, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    if (grobj instanceof UilClientGrobj)
      return ((UilClientGrobj)grobj).uilCallValidateMethodForGrobj(win);
    else if (grobj instanceof UilClientEditBox)
      return ((UilClientEditBox)grobj).uilCallValidateMethodForGrobj(win);
    else throw new IllegalArgumentException("Expected either a UilClientGrobj or UilClientEditBox");
  }

  public static void uilDisableGrobj(UilClientItem grobj){
    grobj.uilDisableGrobj();
  }

  public static void uilDisableGrobjMethod(UilClientItem grobj) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    grobj.uilDisableGrobjMethod();
  }

  public static void uilEnableGrobj(UilClientItem grobj){
    grobj.uilEnableGrobj();
  }

  public static void uilEnableGrobjMethod(UilClientItem grobj) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    grobj.uilEnableGrobjMethod();
  }

  //scroll-area
  public static void uilClearMessages(UilClientScrollArea scrollArea){
    scrollArea.uilClearMessages();
  }

  public static void uilDeleteSelectedMessages(UilClientScrollArea scrollArea){
    scrollArea.uilDeleteSelectedMessages();
  }

  public static void uilDisplayMessageList(UilClientScrollArea scrollArea, int index){
    scrollArea.uilDisplayMessageList(index);
  }

  public static int uilGetIndexOfScrollMessage(UilClientScrollArea scrollArea, UilClientMessageObject msgObject){
    return scrollArea.uilGetIndexOfScrollMessage(msgObject);
  }

  public static UilClientMessageObject uilGetMessageFromIndex(UilClientScrollArea scrollArea, int index){
    return scrollArea.uilGetMessageFromIndex(index);
  }

  public static void uilMessageSelection(UilClientMessageObject msgObject, UilClientScrollArea scrollArea, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    scrollArea.uilMessageSelection(msgObject, win);
  }

  public static void uilMessageSelectionMethod(UilClientMessageObject msgObject, UilClientScrollArea scrollArea, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    scrollArea.uilMessageSelectionMethod(msgObject, win);
  }

  public static void uilMessageUnselection(UilClientMessageObject msgObject, UilClientScrollArea scrollArea, 
					   UiClientItem win){
    scrollArea.uilMessageUnselection(msgObject, win);
  }

  public static void uilMessageUnselectionMethod(UilClientMessageObject msgObject, UilClientScrollArea scrollArea, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    scrollArea.uilMessageUnselectionMethod(msgObject, win);
  }

  public static void uilResetScrollArea(UilClientScrollArea scrollArea){
    scrollArea.uilResetScrollArea();
  }

  //returns (msg, symbol)
  public static void uilAddMessageToList(UilClientScrollArea scrollArea, UilClientMessageObject msgObject){
    scrollArea.uilAddMessageToList(msgObject);
  }

  //uil-move-message

  public static String[] uilGetSelectedMessage(UilClientDialog dlg, String id){
    UilClientItem scrollArea = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (scrollArea instanceof UilClientScrollArea)
      return ((UilClientScrollArea)scrollArea).uilGetSelectedMessage();
    else
      throw new IllegalArgumentException("Control with id="+id+" is not a scroll area");
  }

  public static UilClientMessageObject[] uilGetSelectedMessageObjects(UilClientDialog dlg, String id){
    UilClientItem scrollArea = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (scrollArea instanceof UilClientScrollArea)
      return ((UilClientScrollArea)scrollArea).uilGetSelectedMessageObjects();
    else
      throw new IllegalArgumentException("Control with id="+id+" is not a scroll area");
  }

  public static void uilUpdateScrollAreaFromArray(UilClientScrollArea scrollArea, G2Array array) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    scrollArea.uilUpdateScrollAreaFromArray(array);
  }

  public static void uilUpdateScrollAreaFromList(UilClientScrollArea scrollArea, G2List list) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    scrollArea.uilUpdateScrollAreaFromList(list);
  }

  //message-object
  public static UilClientMessageObject uilCreateMessage(UilClientScrollArea scrollArea, Object value, 
							double priority){
    return scrollArea.uilCreateMessageObject(value, priority);
  }

  public static Symbol uilGetMessageObjectState(UilClientMessageObject msgObject){
    return msgObject.uilGetMessageObjectState();
  }

  public static void uilSelectMessage(UilClientMessageObject msgObject) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    msgObject.uilSelectMessage();
  }

  public static void uilSelectMessageOnWindow(UilClientMessageObject msgObject, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    msgObject.uilSelectMessageOnWindow(win);
  }

  public static void uilUnselectMessage(UilClientMessageObject msgObject){
    msgObject.uilUnselectMessage();
  }

  public static void uilRemoveMessage(UilClientMessageObject msgObject){
    msgObject.uilRemoveMessage();
  }

  public static void uilRemoveMessageFromList(UilClientMessageObject msgObject){
    msgObject.uilRemoveMessageFromList();
  }

  //buttons
  public static void uilAddLabelToButton(UilClientButton button, String label, Symbol size){
    button.uilAddLabelToButton(label, size);
  }

  public static void uilUpdateButtonLabel(UilClientButton button){
  }

  public static void uilDisableButton(UilClientButton button){
    button.uilDisableGrobj();
  }

  public static void uilEnableButton(UilClientButton button){
    button.uilEnableGrobj();
  }

  public static void uilSelectButton(UilClientButton button, UiClientItem win, UilClientDialog dlg) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    button.uilSelectButton(win, dlg);
  }

  //has 3rd arg of wksp
  public static void uilToggleButton(UilClientStateButton button, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    button.uilToggleButton(win);
  }

  public static void uilToggleButtonNoCallback(UilClientStateButton button) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    button.uilToggleButtonNoCallback();
  }

  public static void uilUpdateButtonToggleLabel(UilClientToggleButton button){
    button.uilUpdateButtonToggleLabel();
  }

  public static Symbol uilGetToggleButtonState(UilClientDialog dlg, String id){
    UilClientItem button = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (button instanceof UilClientToggleButton)
      return ((UilClientToggleButton)button).uilGetToggleButtonState();
    else throw new IllegalArgumentException("Expected control with id "+id+" on dialog "+dlg+" to be a UilClientStateButton");
  }

  public static void uilSetToggleButtonState(UilClientDialog dlg, String id, Symbol state) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    UilClientItem button = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (button instanceof UilClientToggleButton)
      ((UilClientToggleButton)button).uilSetToggleButtonState(state);
    else throw new IllegalArgumentException("Expected control with id "+id+" on dialog "+dlg+" to be a UilClientToggleButton");
  }

  //selection box
  /*
  public static Object uilGetCheckBoxValues(UilClientDialog dlg , String id){
    UilClientItem box = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (box instanceof UilClientCheckBox)
      return ((UilClientRadioBox)box).uilCheckBoxValues();
  }

  public static void uilSetCheckBoxValues(UilClientDialog dlg , String id, TextArray values){
  }
  */

  public static Object uilGetRadioBoxValue(UilClientDialog dlg, String id){
    UilClientItem box = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (box instanceof UilClientRadioBox)
      return ((UilClientRadioBox)box).uilGetRadioBoxValue();
    else throw new IllegalArgumentException("Expected control with id "+id+" on dialog "+dlg+" to be a UilClientRadioButton");
  }

  public static void uilSetRadioBoxValue(UilClientDialog dlg, String id, Object value, UiClientItem win) 
       throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    UilClientItem box = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (box instanceof UilClientRadioBox)
      ((UilClientRadioBox)box).uilSetRadioBoxValue(value);
  }

  //edit-box
  public static Object uilGetEditBoxValue(UilClientDialog dlg, String id){
    UilClientItem editBox = dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
    if (editBox instanceof UilClientEditBox)
      return ((UilClientEditBox)editBox).uilGetEditBoxValue();
    else throw new IllegalArgumentException("Expected control with id "+id+" on dialog "+dlg+" to be a UilClientEditBox");
  }

  public static void uilUpdateEditBoxLabel(UilClientEditBox editBox){
    editBox.uilUpdateEditBoxLabel();
  }

  public static void uilEditBoxSelection(UilClientEditBox editBox, UilClientDialog dlg, UiClientItem win){
    editBox.uilEditBoxSelection(dlg, win);
  }

  public static void uilEditBoxSelectionMethod(UilClientEditBox editBox, UilClientDialog dlg, 
					       UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    editBox.uilEditBoxSelectionMethod(dlg, win);
  }

  public static void uilEditBoxUnselection(UilClientEditBox editBox, UilClientDialog dlg, UiClientItem win,
					   Boolean committed) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    editBox.uilEditBoxUnselection(dlg, win, committed);
  }

  public static void uilEditBoxUnselectionMethod(UilClientEditBox editBox, UilClientDialog dlg, 
						 UiClientItem win, Boolean committed) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    editBox.uilEditBoxUnselectionMethod(dlg, win, committed);
  }

  public static void uilSelectEditBox(UilClientEditBox editBox, UilClientDialog dlg, UiClientItem win)throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    editBox.uilSelectEditBox(dlg, win);
  }

  public static void uilSelectEditBoxOnDialog(UilClientEditBox editBox, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    editBox.uilSelectEditBoxOnDialog(win);
  }

  //uil-commit-edit-session-result-to-edit-box
  //uil-register-edit-session-results
  //uil-launch-edit-session

  //text
  public static void uilUpdateText(UilClientGrmes grmes, Object value){
    grmes.uilUpdateText(value);
  }

  public static void uilUpdateUnformattedtext(UilClientGrmes grmes, Object value){
  }

  //dialog
  public static Item uilFindInitiatingObject(UilClientDialog dlg){
    return dlg.uilFindInitiatingObject();
  }

  public static UilClientItem uilGetGrobjFromIdOnDlgOrWksp(String id, UilClientDialog dlg){
    return dlg.uilGetGrobjFromIdOnDlgOrWksp(id);
  }

  public static void uilSimulatePlayMode(UilClientDialog dlg){
    dlg.uilSimulatePlayMode();
  }

  public static void uilUnsimulatePlayMode(UilClientDialog dlg){
    dlg.uilUnsimulatePlayMode();
  }

  public static void uilShowManagedDialog(UilClientDialog dlg){
    dlg.uilShowManagedDialog();
  }

  public static void uilHideManagedDialog(UilClientDialog dlg, UiClientItem win){
    dlg.uilHideManagedDialog();
  }

  public static void uilReleaseDialog(UilClientDialog dlg, UiClientItem win, boolean deleteRelatedItem){
    dlg.uilReleaseDialog();
  }

  public static void uilFlushDialogEventQueue(UilClientDialog dlg, UiClientItem win, Object actionQueue){
    dlg.uilFlushDialogEventQueue();
  }

  //in UIL API args = actionQueue only
  public static void uilRemoveAllRemainingActions(UilClientDialog dlg, Object actionQueue){
    dlg.uilRemoveAllRemainingActions();
  }

  public static void uilInsertActionsIntoDialogEventQueue(Object actions, UilClientDialog dlg, 
							  UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    dlg.uilInsertActionsIntoDialogEventQueue(actions, win);
  }

  public static UilClientDialog uilGetParentDialog(UilClientDialog dlg){
    return dlg.getParentDialog();
  }

  public static Item uilFindInitiatingObjectForParentDialog(UilClientDialog dlg){
    UilClientDialog parent = dlg.getParentDialog();
    if (parent != null)
      return parent.uilFindInitiatingObject();
    else
      return dlg.uilFindInitiatingObject();//this is how it is implemented in UIL
  }
  //uil-end-dialog-edit
  //uil-quit-dialog-edit
  //uil-get-active-dialog-on-window-if-one-exists

  public static boolean isDefaultAction(Symbol action){
    return UILDialogProxy.isDefaultAction(action);
  }

  public static void uilDoNothing(){
  }

  public static TwAccess getConnection(UilClientDialog dlg){
    return dlg.getConnection();
  }
}




