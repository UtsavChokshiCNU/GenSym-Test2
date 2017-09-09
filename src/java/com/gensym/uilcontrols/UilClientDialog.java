package com.gensym.uilcontrols;

import java.awt.Component;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.classes.Item;
import com.gensym.classes.SymbolArray;
import com.gensym.classes.UiClientItem;

public interface UilClientDialog extends UilClientGrobj{

  //actions
  public static final Symbol UIL_CALL_VALIDATE_METHOD_ = Symbol.intern("UIL-CALL-VALIDATE-METHOD");
  public static final Symbol UIL_CALL_CONCLUDE_METHOD_ = Symbol.intern("UIL-CALL-CONCLUDE-METHOD");
  public static final Symbol UIL_CALL_CONCLUDE_METHOD_FOR_PARENT_ = Symbol.intern("UIL-CALL-CONCLUDE-METHOD-FOR-PARENT");
  public static final Symbol UIL_CALL_CONCLUDE_METHOD_FOR_CHILDREN_ = Symbol.intern("UIL-CALL-CONCLUDE-METHOD-FOR-CHILDREN");
  public static final Symbol UIL_CALL_UPDATE_METHOD_ = Symbol.intern("UIL-CALL-UPDATE-METHOD");
  public static final Symbol UIL_CALL_UPDATE_METHOD_FOR_PARENT_ = Symbol.intern("UIL-CALL-UPDATE-METHOD-FOR-PARENT");
  public static final Symbol UIL_CALL_UPDATE_METHOD_FOR_CHILDREN_ = Symbol.intern("UIL-CALL-UPDATE-METHOD-FOR-CHILDREN");
  public static final Symbol UIL_CALL_CONFIGURATION_METHOD_ = Symbol.intern("UIL-CALL-CONFIGURATION-METHOD");
  public static final Symbol UIL_SIMULATE_PLAY_MODE_ = Symbol.intern("UIL-SIMULATE-PLAY-MODE");
  public static final Symbol UIL_SHOW_DIALOG_ = Symbol.intern("UIL-SHOW-DIALOG");
  public static final Symbol UIL_HIDE_DIALOG_ = Symbol.intern("UIL-HIDE-DIALOG");
  public static final Symbol UIL_UNSIMULATE_PLAY_MODE_ = Symbol.intern("UIL-UNSIMULATE-PLAY-MODE");
  public static final Symbol UIL_RELEASE_TEMPORARY_STORAGE_OBJECT_ = Symbol.intern("UIL-RELEASE-TEMPORARY-STORGAE-OBJECT");
  public static final Symbol UIL_DELETE_TEMPORARY_STORAGE_OBJECT_ = Symbol.intern("UIL-DELETE-TEMPORARY-STORAGE-OBJECT");
  public static final Symbol UIL_RETURN_DIALOG_ = Symbol.intern("UIL-RETURN-DIALOG");
  public static final Symbol UIL_RELEASE_DIALOG_ = Symbol.intern("UIL-RELEASE-DIALOG");
  public static final Symbol UIL_DELETE_DIALOG_ = Symbol.intern("UIL-DELETE-DIALOG");

  //properties
  public Symbol getUilInitiatingClassForDialog();
  public Symbol getUilTemporaryStorageObject();
  public Object getUilWhichButtonPressed();
  public Symbol getUilReturnKeyBehavior();
  public Symbol getUilTabKeyBehavior();
  public Symbol getUilAbortKeyBehavior();
  public boolean getUilDialogHasMovableWorkspace();
  public boolean getUilDialogEditBoxesHaveMenus();
  public Symbol getUilOrigin();
  public boolean getUilAllowMultipleCopiesPerWindow();
  public boolean getUilDialogAllowOutsideTextSelection();
  public Symbol getUilDialogHomeModuleName();
  public int getUilDialogInstancePoolLimit();
  public boolean getUilDialogInUse();
  public boolean getUilAlwaysUpdateWhenManaged();
  public boolean getUilUseDefaultPositioning();
  public boolean getUilAllowLiftToTop();
  public boolean getUilTranslateDialog();
  public Symbol getUilGfrTextResourceGroup();

  //API
  public UilClientItem uilGetGrobjFromIdOnDlgOrWksp(String id);
  public Item uilFindInitiatingObject();
  public void uilSimulatePlayMode();
  public void uilUnsimulatePlayMode();
  public void uilShowManagedDialog();
  public void uilHideManagedDialog();
  public void uilReleaseDialog();
  public void uilFlushDialogEventQueue();
  public void uilRemoveAllRemainingActions();
  public void uilInsertActionsIntoDialogEventQueue(Object actions, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;
  public void uilControlDialogCallback(UilCallback[] actions, Object initObj, UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException;

  //misc
  public ItemProxy getProxy();
  public void setProxy(ItemProxy proxy);
  //public void setDialogCommand(DialogCommand cmdBean);
  public UiClientItem getWindow();
  public TwAccess getConnection();
  public UilClientDialog getParentDialog();
  public void setParentDialog(UilClientDialog dlg);
  public UilClientDialog[] getChildDialogs();
  public void addChildDialog(UilClientDialog dlg);
  public void removeChildDialog(UilClientDialog dlg);
  public void setDefaultButton(UilClientPushbutton button);
  public void setCancelButton(UilClientPushbutton button);
  public void addControl(UilClientItem control);
  public void cancel()throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException;
  public void launch() throws G2AccessException, ClassNotFoundException, InvocationTargetException,
	 NoSuchMethodException, IllegalAccessException;
  public UilCallback[] getLaunchActions();
  public void setLaunchActions(UilCallback[] actions);
  public boolean customLaunchActions();
  public void setTitle(String title);
  public String getTitle();
  public UilClientItem[] getUilClientItems();
  public UilClientButton getButtonThatLaunchedDialog();
  public void setButtonThatLaunchedDialog(UilClientButton button);
  public Component getLastComponentToLoseFocus();
}
