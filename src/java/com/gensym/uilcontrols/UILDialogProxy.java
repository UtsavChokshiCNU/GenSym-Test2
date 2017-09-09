package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.Dialog;
import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.classes.Item;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilTailoredDialog;
import com.gensym.classes.modules.uillib.UilActionDescriptionArray;

public class UILDialogProxy extends DialogCommand implements UilClientDialog, Serializable{

  static final long serialVersionUID = 6380455052213616413L;

  private UilClientDialog uilHelper;
  private Object launchArrayName;
  private String title;
  private Dialog dialog;

  public UILDialogProxy(UilTailoredDialog dlg, UilActionDescriptionArray launchArray, Class staticClass) 
       throws G2AccessException{
    uilHelper = new UilClientDialogImpl(dlg, launchArray, staticClass, this);
    if (launchArray != null)
      launchArrayName = launchArray.getNames();
  }

  @Override
  public String getTitle(){
    return title;
  }

  @Override
  public void setTitle(String title){
    this.title = title;
    if (dialog != null)
      dialog.setTitle(title);
  }

  public void setDialog(Dialog dlg){
    this.dialog = dlg;
    if (title != null)
      dlg.setTitle(title);
  }

  public Object getLaunchArrayName(){
    return launchArrayName;
  }

  @Override
  public void open () {
    try{
      uilHelper.launch();
      super.open();
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

   @Override
  public void close() {
     try{
       uilHelper.cancel();
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

  void closeDialog(){
    super.close();
  }

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
  public Symbol getUilInitiatingClassForDialog(){
    return uilHelper.getUilInitiatingClassForDialog();
  }
  @Override
  public Symbol getUilTemporaryStorageObject(){
    return uilHelper.getUilTemporaryStorageObject();
  }
  @Override
  public Object getUilWhichButtonPressed(){
    return uilHelper.getUilWhichButtonPressed();
  }
  @Override
  public Symbol getUilReturnKeyBehavior(){
    return uilHelper.getUilReturnKeyBehavior();
  }
  @Override
  public Symbol getUilTabKeyBehavior(){
    return uilHelper.getUilTabKeyBehavior();
  }
  @Override
  public Symbol getUilAbortKeyBehavior(){
    return uilHelper.getUilAbortKeyBehavior();
  }
  @Override
  public boolean getUilDialogHasMovableWorkspace(){
    return uilHelper.getUilDialogHasMovableWorkspace();
  }
  @Override
  public boolean getUilDialogEditBoxesHaveMenus(){
    return uilHelper.getUilDialogEditBoxesHaveMenus();
  }
  @Override
  public Symbol getUilOrigin(){
    return uilHelper.getUilOrigin();
  }
  @Override
  public boolean getUilAllowMultipleCopiesPerWindow(){
    return uilHelper.getUilAllowMultipleCopiesPerWindow();
  }
  @Override
  public boolean getUilDialogAllowOutsideTextSelection(){
    return uilHelper.getUilDialogAllowOutsideTextSelection();
  }
  @Override
  public Symbol getUilDialogHomeModuleName(){
    return uilHelper.getUilDialogHomeModuleName();
  }
  @Override
  public int getUilDialogInstancePoolLimit(){
    return uilHelper.getUilDialogInstancePoolLimit();
  }
  @Override
  public boolean getUilDialogInUse(){
    return uilHelper.getUilDialogInUse();
  }
  @Override
  public boolean getUilAlwaysUpdateWhenManaged(){
    return uilHelper.getUilAlwaysUpdateWhenManaged();
  }
  @Override
  public boolean getUilUseDefaultPositioning(){
    return uilHelper.getUilUseDefaultPositioning();
  }
  @Override
  public boolean getUilAllowLiftToTop(){
    return uilHelper.getUilAllowLiftToTop();
  }
  @Override
  public boolean getUilTranslateDialog(){
    return uilHelper.getUilTranslateDialog();
  }
  @Override
  public Symbol getUilGfrTextResourceGroup(){
    return uilHelper.getUilGfrTextResourceGroup();
  }
  @Override
  public void setProxy(ItemProxy proxy){
    uilHelper.setProxy(proxy);
  }
  @Override
  public ItemProxy getProxy(){
    return uilHelper.getProxy();
  }
  @Override
  public UiClientItem getWindow(){
    return uilHelper.getWindow();
  }
  @Override
  public TwAccess getConnection(){
    return uilHelper.getConnection();
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
  public void uilDisableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
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
  public UilClientItem uilGetGrobjFromIdOnDlgOrWksp(String id){
    return uilHelper.uilGetGrobjFromIdOnDlgOrWksp(id);
  }
  @Override
  public Item uilFindInitiatingObject(){
    return uilHelper.uilFindInitiatingObject();
  }
  @Override
  public void uilSimulatePlayMode(){
    uilHelper.uilSimulatePlayMode();
  }
  @Override
  public void uilUnsimulatePlayMode(){
    uilHelper.uilUnsimulatePlayMode();
  }
  @Override
  public void uilShowManagedDialog(){ 
    uilHelper.uilShowManagedDialog();
  }
  @Override
  public void uilHideManagedDialog(){ 
    uilHelper.uilHideManagedDialog();
  }
  @Override
  public void uilReleaseDialog(){
    uilHelper.uilReleaseDialog();
  }
  @Override
  public void uilFlushDialogEventQueue(){
    uilHelper.uilFlushDialogEventQueue();
  }
  @Override
  public void uilRemoveAllRemainingActions(){
    uilHelper.uilRemoveAllRemainingActions();
  }
  @Override
  public void uilInsertActionsIntoDialogEventQueue(Object actionList, UiClientItem win) 
       throws G2AccessException,  ClassNotFoundException, InvocationTargetException, NoSuchMethodException, 
	 IllegalAccessException{
	 uilHelper.uilInsertActionsIntoDialogEventQueue(actionList, win);
  }
  @Override
  public void uilControlDialogCallback(UilCallback[] actions, Object initObj, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilControlDialogCallback(actions, initObj, win);
  }
  //misc
  @Override
  public UilClientDialog getParentDialog(){
    return uilHelper.getParentDialog();
  }
  @Override
  public void setParentDialog(UilClientDialog dlg){
    uilHelper.setParentDialog(dlg);
  }
  @Override
  public UilClientDialog[] getChildDialogs(){
    return uilHelper.getChildDialogs();
  }
  @Override
  public void addChildDialog(UilClientDialog dlg){
    uilHelper.addChildDialog(dlg);
  }
  @Override
  public void removeChildDialog(UilClientDialog dlg){
    uilHelper.removeChildDialog(dlg);
  }
  @Override
  public void setDefaultButton(UilClientPushbutton button){
    uilHelper.setDefaultButton(button);
  }
  @Override
  public void setCancelButton(UilClientPushbutton button){
    uilHelper.setCancelButton(button);
  }
  @Override
  public void addControl(UilClientItem control){
    uilHelper.addControl(control);
  }
  @Override
  public void cancel()throws G2AccessException, ClassNotFoundException, InvocationTargetException,
    NoSuchMethodException, IllegalAccessException{
      uilHelper.cancel();
  }
  @Override
  public void launch() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
    NoSuchMethodException, IllegalAccessException{
      uilHelper.launch();
  }
  @Override
  public UilCallback[] getLaunchActions(){
    return uilHelper.getLaunchActions();
  }
  @Override
  public void setLaunchActions(UilCallback[] actions){
    uilHelper.setLaunchActions(actions);
  }
  @Override
  public boolean customLaunchActions(){
    return uilHelper.customLaunchActions();
  }

  @Override
  public UilClientItem[] getUilClientItems(){
    return uilHelper.getUilClientItems();
  }

  @Override
  public UilClientButton getButtonThatLaunchedDialog(){
    return uilHelper.getButtonThatLaunchedDialog();
  }

  @Override
  public void setButtonThatLaunchedDialog(UilClientButton button){
    uilHelper.setButtonThatLaunchedDialog(button);
  }

  @Override
  public Component getLastComponentToLoseFocus(){
    return uilHelper.getLastComponentToLoseFocus();
  }

  private static final Symbol[] DEFAULT_ACTIONS = new Symbol[] {UIL_CALL_VALIDATE_METHOD_, UIL_CALL_CONCLUDE_METHOD_,  UIL_CALL_CONCLUDE_METHOD_FOR_PARENT_, UIL_CALL_CONCLUDE_METHOD_FOR_PARENT_, UIL_CALL_CONCLUDE_METHOD_FOR_CHILDREN_, UIL_CALL_CONCLUDE_METHOD_FOR_CHILDREN_, UIL_CALL_UPDATE_METHOD_, UIL_CALL_UPDATE_METHOD_FOR_PARENT_, UIL_CALL_UPDATE_METHOD_FOR_CHILDREN_, UIL_CALL_CONFIGURATION_METHOD_, UIL_SIMULATE_PLAY_MODE_, UIL_SHOW_DIALOG_, UIL_HIDE_DIALOG_, UIL_UNSIMULATE_PLAY_MODE_, UIL_RELEASE_TEMPORARY_STORAGE_OBJECT_, UIL_DELETE_TEMPORARY_STORAGE_OBJECT_, UIL_RETURN_DIALOG_,  UIL_RELEASE_DIALOG_, UIL_DELETE_DIALOG_};

  //support
  public static boolean isDefaultAction(Symbol action){
    for (int i=0; i<DEFAULT_ACTIONS.length; i++)
      if (DEFAULT_ACTIONS[i].equals(action))
	return true;
    return false;
  }

}
