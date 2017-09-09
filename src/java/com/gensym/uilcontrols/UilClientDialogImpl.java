package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.event.FocusListener;
import java.awt.event.FocusEvent;
import java.io.Serializable;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.controls.ItemProxy;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.SymbolArray;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilTailoredDialog;
import com.gensym.classes.modules.uillib.UilActionDescriptionArray;

public class UilClientDialogImpl extends UilClientGrobjImpl implements UilClientDialog, FocusListener, Serializable{

  static final long serialVersionUID = -7638880894036640083L;

  private Symbol uilInitiatingClassForDialog;
  private Symbol uilTemporaryStorageObject;
  private Object uilWhichButtonPressed;
  private Symbol uilTabKeyBehavior;
  private Symbol uilReturnKeyBehavior;
  private Symbol uilAbortKeyBehavior;
  private boolean uilDialogHasMovableWorkspace;
  private boolean uilDialogEditBoxesHaveMenus;
  private Symbol uilOrigin;
  private boolean uilAllowMultipleCopiesPerWindow;
  private boolean uilDialogAllowOutsideTextSelection;
  private Symbol uilDialogHomeModuleName;
  private int uilDialogInstancePoolLimit;
  private boolean uilDialogInUse;
  private boolean uilAlwaysUpdateWhenManaged;
  private boolean uilUseDefaultPositioning;
  private boolean uilAllowLiftToTop;
  private boolean uilTranslateDialog;
  private Symbol uilGfrTextResourceGroup;

  private transient UilClientDialog parent;
  protected transient Vector children;
  
  private UilClientPushbutton defaultButton;
  private UilClientPushbutton cancelButton;

  private Hashtable controlsTable;
  private Vector controlsList;
  private ItemProxy proxy;
  private TwAccess connection;
  private UiClientItem win;
  private UilCallback[] launchActions;
  private boolean customLaunchActions = false;
  private Vector actionQueue;
  private boolean executing = false;
  private UilClientButton launchingButton;
  private Component lastComponentToLoseFocus;

  private UILDialogProxy dlgProxy;

  public UilClientDialogImpl(UilTailoredDialog dlg, UilActionDescriptionArray launchArray, Class staticClass,
			     UILDialogProxy dlgProxy) throws G2AccessException{
    super(dlg, null, staticClass);
    this.dlgProxy = dlgProxy;
    controlsTable = new Hashtable();
    controlsList = new Vector();
    actionQueue = new Vector();
    if (launchArray != null){
      setLaunchActions(launchArray, staticClass);
    }
  }

  private void setLaunchActions(UilActionDescriptionArray launchArray, Class staticClass) 
       throws G2AccessException{
    SymbolArray actionArray = (SymbolArray)launchArray.getUilActionSpecifics();
    if (actionArray != null){
      Sequence actions = actionArray.getG2ArraySequence();
      if (actions != null){
	launchActions = new UilCallback[actions.size()];
	Enumeration actionList = actions.elements();
	int i = 0;
	while (actionList.hasMoreElements()){
	  Symbol action = (Symbol)actionList.nextElement();
	  UilCallback callback;
	  if (dlgProxy.isDefaultAction(action)) 
	    callback= new UilCallback(action, UilClientConstants.ACTION_ARG_TYPES, 
				      UilClientConstants.ACTION_ARGS);
	  else{
	    customLaunchActions = true;
	    String methodName = UilCallback.convertCallbackNameToMethodName(action);
	    callback = new UilCallback(action, UilClientConstants.ACTION_ARG_TYPES, 
				       UilClientConstants.ACTION_ARGS, staticClass, methodName);
	  }
	  launchActions[i++] = callback;
	}
      }
    }
  }

  @Override
  public Component getLastComponentToLoseFocus(){
    return lastComponentToLoseFocus;
  }

  @Override
  public boolean customLaunchActions(){
    return customLaunchActions;
  }

  @Override
  public void setLaunchActions(UilCallback[] actions){
    //System.out.println("setLaunchActions:"+actions);
    this.launchActions = actions;
  }

  @Override
  public UilCallback[] getLaunchActions(){
    UilCallback[] actions = new UilCallback[launchActions.length];
    for (int i=0; i< launchActions.length; i++)
      actions[i] = launchActions[i];
    return actions;
  }

  //properties
  @Override
  public Symbol getUilInitiatingClassForDialog(){
    return uilInitiatingClassForDialog;
  }

  @Override
  public Symbol getUilTemporaryStorageObject(){
    return uilTemporaryStorageObject;
  }

  @Override
  public Object getUilWhichButtonPressed(){
    return uilWhichButtonPressed;
  }

  @Override
  public Symbol getUilReturnKeyBehavior(){
    return uilReturnKeyBehavior;
  }

  @Override
  public Symbol getUilTabKeyBehavior(){
    return uilTabKeyBehavior;
  }

  @Override
  public Symbol getUilAbortKeyBehavior(){
    return uilAbortKeyBehavior;
  }

  @Override
  public boolean getUilDialogHasMovableWorkspace(){
    return uilDialogHasMovableWorkspace;
  }

  @Override
  public boolean getUilDialogEditBoxesHaveMenus(){
    return uilDialogEditBoxesHaveMenus;
  }

  @Override
  public Symbol getUilOrigin(){
    return uilOrigin;
  }

  @Override
  public boolean getUilAllowMultipleCopiesPerWindow(){
    return uilAllowMultipleCopiesPerWindow;
  }

  @Override
  public boolean getUilDialogAllowOutsideTextSelection(){
    return uilDialogAllowOutsideTextSelection;
  }

  @Override
  public Symbol getUilDialogHomeModuleName(){
    return uilDialogHomeModuleName;
  }

  @Override
  public int getUilDialogInstancePoolLimit(){
    return uilDialogInstancePoolLimit;
  }

  @Override
  public boolean getUilDialogInUse(){
    return uilDialogInUse;
  }

  @Override
  public boolean getUilAlwaysUpdateWhenManaged(){
    return uilAlwaysUpdateWhenManaged;
  }

  @Override
  public boolean getUilUseDefaultPositioning(){
    return uilUseDefaultPositioning;
  }

  @Override
  public boolean getUilAllowLiftToTop(){
    return uilAllowLiftToTop;
  }

  @Override
  public boolean getUilTranslateDialog(){
    return uilTranslateDialog;
  }

  @Override
  public Symbol getUilGfrTextResourceGroup(){
    return uilGfrTextResourceGroup;
  }

  @Override
  public void setProxy(ItemProxy proxy){
    this.proxy = proxy;
  }

  @Override
  public ItemProxy getProxy(){
    return proxy;
  }

  @Override
  public UiClientItem getWindow(){
    return win;
  }

  @Override
  public TwAccess getConnection(){
    return connection;
  }

  //API
  @Override
  public UilClientItem uilGetGrobjFromIdOnDlgOrWksp(String id){
    return (UilClientItem)controlsTable.get(id.toLowerCase());
  }

  @Override
  public Item uilFindInitiatingObject(){//more than this...sub-dlg stuff
    if (proxy == null) return null;
    return proxy.getProxy();
  }

  @Override
  public void uilSimulatePlayMode(){
    //System.out.println("dlg.uilSimulatePlayMode");
  }

  @Override
  public void uilUnsimulatePlayMode(){
    //System.out.println("dlg.uilUnSimulatePlayMode");
  }

  @Override
  public void uilShowManagedDialog(){ 
    //System.out.println("dlg.uilShowManagedDialog");
  }

  @Override
  public void uilHideManagedDialog(){ 
    //System.out.println("dlg.uilHideManagedDialog");
  }

  @Override
  public void uilReleaseDialog(){
    UilClientDialog[] dlgs = getChildDialogs();
    if (dlgs != null){
      for (int i=0; i<dlgs.length; i++){
	dlgs[i].uilUnsimulatePlayMode();
	dlgs[i].uilHideManagedDialog();
	dlgs[i].uilReleaseDialog();
      }
    }
    UilClientDialog parent = getParentDialog();
    if (parent != null)
      parent.removeChildDialog(dlgProxy);
    if (dlgProxy != null)
      dlgProxy.closeDialog();
  }

  @Override
  public void uilFlushDialogEventQueue(){
    uilRemoveAllRemainingActions();
  }

  @Override
  public void uilRemoveAllRemainingActions(){
    actionQueue.removeAllElements();
  }

  @Override
  public void uilInsertActionsIntoDialogEventQueue(Object actionList, UiClientItem win) 
       throws G2AccessException, 
	 ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
    if (actionList instanceof SymbolArray){
      Enumeration actions = ((SymbolArray)actionList).getG2ArraySequence().elements();
      while (actions.hasMoreElements())
	actionQueue.addElement(actions.nextElement());
      executeActions();
    }
    else throw new IllegalArgumentException("actionList should be a SymbolArray");
  }

  @Override
  public void uilControlDialogCallback(UilCallback[] actions, Object initObj, 
				       UiClientItem win) throws G2AccessException, ClassNotFoundException, 
	   InvocationTargetException, NoSuchMethodException, IllegalAccessException{
	     //System.out.println("dlg.controlDialogCallback: actions="+actions+" initObj="+initObj);
    for (int i=0; i<actions.length; i++){
      UilCallback action = actions[i];
      action.setObjectInitiatingCallback(initObj);
      actionQueue.addElement(action);
    }
    executeActions();
  }

  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			       Object actionQueue) throws G2AccessException{
    try{
      Enumeration controls = controlsList.elements();
      while (controls.hasMoreElements()){
	Object control = controls.nextElement();
	if (control instanceof UilClientGrobj){
	  UilClientGrobj grobj = (UilClientGrobj)control;
	  if (!(grobj instanceof UilClientRadioButton)  && !(grobj instanceof UilClientCheckButton))
	    grobj.uilConcludeGrobjMethod(win, dlg, button, actionQueue);
	}
	else if (control instanceof UilClientEditBox)
	  ((UilClientEditBox)control).uilConcludeGrobjMethod(win, dlg, button, actionQueue);
	else if (control instanceof UilClientMessageObject)
	  ((UilClientMessageObject)control).uilConcludeGrobjMethod(win, dlg, button, actionQueue);
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
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			     Object actionQueue) throws G2AccessException{
    try{
      //System.out.println("dlg.uilUpdateGrobj");
      Enumeration controls = controlsList.elements();
      while (controls.hasMoreElements()){
	UilClientItem grobj = (UilClientItem)controls.nextElement();
	if (!(grobj instanceof UilClientRadioButton)  && !(grobj instanceof UilClientCheckButton))
	  grobj.uilUpdateGrobjMethod(win, dlg, button, actionQueue);
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
  public void uilDisableGrobj(){
    try{
      Enumeration controls = controlsList.elements();
      while (controls.hasMoreElements()){
	UilClientItem grobj = (UilClientItem)controls.nextElement();
	if (!(grobj instanceof UilClientRadioButton)  && !(grobj instanceof UilClientCheckButton))
	  grobj.uilDisableGrobjMethod();
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
  public void uilEnableGrobj(){
    try{
      Enumeration controls = controlsList.elements();
      while (controls.hasMoreElements()){
	UilClientItem grobj = (UilClientItem)controls.nextElement();
	if (!(grobj instanceof UilClientRadioButton)  && !(grobj instanceof UilClientCheckButton))
	  grobj.uilEnableGrobjMethod();
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
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object button, Object actionQueue){
    try{
      Enumeration controls = controlsList.elements();
      String result = UilClientConstants.OK;
      while (controls.hasMoreElements()){
	Object control = controls.nextElement();
	if (control instanceof UilClientEditBox)
	  result = ((UilClientEditBox)control).uilValidateGrobjMethod(win, dlg, button, actionQueue);
	if (!result.toLowerCase().equals(UilClientConstants.OK)) return result;
      }
      return result;
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

  //misc

  @Override
  public void setTitle(String title){
    dlgProxy.setTitle(title);
  }

  @Override
  public String getTitle(){
    return dlgProxy.getTitle();
  }

  @Override
  public UilClientDialog getParentDialog(){
    return parent;
  }

  @Override
  public void setParentDialog(UilClientDialog dlg){
    parent = dlg;
  }

  @Override
  public UilClientDialog[] getChildDialogs(){
    if (children == null) return null;
    if (children.size() == 0) return null;
    UilClientDialog[] dlgs = new UilClientDialog[children.size()];
    children.copyInto(dlgs);
    return dlgs;
  }

  @Override
  public void addChildDialog(UilClientDialog dlg){
    //System.out.println("children="+children);
    if (children == null) children = new Vector();
    children.addElement(dlg);
    //System.out.println("dlg="+dlg);
    dlg.setParentDialog(this);
  }

  @Override
  public void removeChildDialog(UilClientDialog dlg){
    children.removeElement(dlg);
  }

  @Override
  public void setDefaultButton(UilClientPushbutton button){
    this.defaultButton = button;
  }

  @Override
  public void setCancelButton(UilClientPushbutton button){
    this.cancelButton = button;
  }

  @Override
  public void addControl(UilClientItem control){
    addControl0(control);
    if (control instanceof UilClientSelectionBox){
      UilClientStateButton[] buttons = ((UilClientSelectionBox)control).getMembers();
      for (int i=0; i<buttons.length; i++)	
	addControl0(buttons[i]);
    }
  }

  private void addControl0(UilClientItem control){
    controlsTable.put(control.getId().toLowerCase(), control);
    controlsList.addElement(control);
    control.setDialogProxy(dlgProxy);
    if (control instanceof Component)
      ((Component)control).addFocusListener(this);
  }

  @Override
  public void cancel() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
    //System.out.println("dlg.cancel");
    //System.out.println("cancelButton="+cancelButton);
    if (cancelButton == null)
      doDefaultCancelActions();
    else
      cancelButton.uilSelectButton(win, this);
  }

  private void doDefaultCancelActions(){
    uilHideManagedDialog();
    uilUnsimulatePlayMode();
    uilReleaseDialog();
  }

  @Override
  public void launch() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
    if (proxy != null){
      Item item = proxy.getProxy();
      if (item != null)
	connection = (TwAccess)((ImplAccess)item).getContext();
      else if (parent != null)
	connection = parent.getConnection();
    }
    if (connection != null)
      win = connection.retrieveSession();
    Enumeration controls = controlsList.elements();
    while (controls.hasMoreElements()){
      UilClientItem grobj = (UilClientItem)controls.nextElement();
      grobj.setDialogProxy(this);
    }
    //System.out.println("launchActions = "+launchActions);
    if (launchActions == null)
      doDefaultLaunchActions();
    else
      uilControlDialogCallback(launchActions, proxy.getProxy(), win);
  }

  @Override
  public UilClientButton getButtonThatLaunchedDialog(){
    return launchingButton;
  }

  @Override
  public void setButtonThatLaunchedDialog(UilClientButton button){
    launchingButton = button;
  }

  //support
  private void doDefaultLaunchActions() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
    uilCallUpdateMethodForGrobj(win);
    uilSimulatePlayMode();
    uilShowManagedDialog();
  }
  
  private void executeActions() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
    //System.out.println("dlg.executeActions: executing="+executing);
    try{
      if (executing) return;
      executing = true;
      executeActions0();
      executing = false;
    }
    catch(Throwable ex){
      executing = false;
      actionQueue.removeAllElements();
      Trace.exception(ex);
      throw new UnexpectedException(ex);
    }
  }

  private void executeActions0() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
    if (actionQueue.size() > 0){
      UilCallback action = (UilCallback)actionQueue.elementAt(0);
      actionQueue.removeElementAt(0);
      if (action.isDefaultCallback())
	executeDefaultAction(action);
      else
	executeCustomAction(action);
      executeActions0();
    }
  }

  private void executeDefaultAction(UilCallback defaultAction) throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException{
    //System.out.println("dlg.executeDefaultAction:"+defaultAction.getName());
    if (defaultAction.getName().equals(UIL_CALL_VALIDATE_METHOD_))
      uilValidateGrobjMethod(win, this, defaultAction.getObjectInitiatingCallback(), null);
    else if (defaultAction.getName().equals(UIL_CALL_CONCLUDE_METHOD_))
      uilConcludeGrobjMethod(win, this, defaultAction.getObjectInitiatingCallback(), null);
    else if (defaultAction.getName().equals(UIL_CALL_CONCLUDE_METHOD_FOR_PARENT_)) {
      UilClientDialog parent = getParentDialog();
      if (parent != null)
	parent.uilConcludeGrobjMethod(win, this, defaultAction.getObjectInitiatingCallback(), null);
    }
    else if (defaultAction.getName().equals(UIL_CALL_CONCLUDE_METHOD_FOR_CHILDREN_)) {
      UilClientDialog[] children = getChildDialogs();
      if (children != null)
	for (int i=0; i<children.length; i++)
	  children[i].uilConcludeGrobjMethod(win, this, defaultAction.getObjectInitiatingCallback(), null);
    }
    else if (defaultAction.getName().equals(UIL_CALL_UPDATE_METHOD_))
      uilUpdateGrobjMethod(win, this, defaultAction.getObjectInitiatingCallback(), null);
    else if (defaultAction.getName().equals(UIL_CALL_UPDATE_METHOD_FOR_PARENT_)) {
      UilClientDialog parent = getParentDialog();
      if (parent != null)
	parent.uilUpdateGrobjMethod(win, this, defaultAction.getObjectInitiatingCallback(), null);
    }
    else if (defaultAction.getName().equals(UIL_CALL_UPDATE_METHOD_FOR_CHILDREN_)) {
      UilClientDialog[] children = getChildDialogs();
      if (children != null)
	for (int i=0; i<children.length; i++)
	  children[i].uilUpdateGrobjMethod(win, this, 
					   defaultAction.getObjectInitiatingCallback(), null);
    }
    else if (defaultAction.getName().equals(UIL_CALL_CONFIGURATION_METHOD_)) {}//ignore
    else if (defaultAction.getName().equals(UIL_SIMULATE_PLAY_MODE_))
      uilSimulatePlayMode();
    else if (defaultAction.getName().equals(UIL_SHOW_DIALOG_))
      uilShowManagedDialog();
    else if (defaultAction.getName().equals(UIL_HIDE_DIALOG_))
      uilHideManagedDialog();
    else if (defaultAction.getName().equals(UIL_UNSIMULATE_PLAY_MODE_))
      uilUnsimulatePlayMode(); 
    else if (defaultAction.getName().equals(UIL_RELEASE_TEMPORARY_STORAGE_OBJECT_)) {}//ignore
    else if (defaultAction.getName().equals(UIL_DELETE_TEMPORARY_STORAGE_OBJECT_)) {}//ignore
      else if (defaultAction.getName().equals(UIL_RETURN_DIALOG_)) {}//can't do this
    else if (defaultAction.getName().equals(UIL_RELEASE_DIALOG_))
      uilReleaseDialog();
    else if (defaultAction.getName().equals(UIL_DELETE_DIALOG_)) {}//don't cache?
    else throw new IllegalArgumentException(defaultAction.getName()+" is not a default action.");
  }
    
  private void executeCustomAction(UilCallback customAction) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    //System.out.println("dlg.executeCustomAction:"+customAction);
      customAction.doCallback(new Object[]{this, customAction.getObjectInitiatingCallback(), 
					     win, proxy.getProxy(), null});
  }

  @Override
  public UilClientItem[] getUilClientItems(){
    UilClientItem[] controls = new UilClientItem[controlsList.size()];
    controlsList.copyInto(controls);
    return controls;
  }

  @Override
  public void focusGained(FocusEvent event){
    //do nothing
  }

  @Override
  public void focusLost(FocusEvent event){
    lastComponentToLoseFocus = (Component)event.getSource();
  }

}
