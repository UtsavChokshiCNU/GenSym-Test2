/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   GMSModuleHandler.java 
 * 
 * 
 */ 
 

package com.gensym.clscupgr.gms;

import javax.swing.JFrame;

import com.gensym.clscupgr.ModuleHandler;
import com.gensym.core.GensymApplication;
import com.gensym.core.UiApplication;
import com.gensym.jgi.G2AccessException;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIManager;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;

/**
 * Listens to notifications from GMS procedures and dispatches them
 */
public class GMSModuleHandler implements ModuleHandler {

  private static Resource i18n = Resource.getBundle("com.gensym.clscupgr.gms.Messages");

  /**
   * @undocumented
   */
  protected static final Symbol HANDLEMENUNOTIFICATION_ = Symbol.intern ("HANDLEMENUNOTIFICATION");

  private TwAccess twAccess;
  private boolean frameAllowedMenuModifications;
  private JFrame frame;
  private MenuManager menuManager;

  public GMSModuleHandler(JFrame frame, TwAccess twAccess) throws G2AccessException{
    this.twAccess = twAccess;
    this.frame = frame;
    initialize();
  }

  // moduleHandler methods
  @Override
  public void moduleLoaded (TwAccess cxn, Symbol moduleName_) {
    changeFrameState();
  }

  @Override
  public void moduleUnloaded (TwAccess cxn, Symbol moduleName_) {
    restoreFrameState();
  }

  // end moduleHandler methods

  public TwAccess getTwAccess(){
    return twAccess;
  }

  public JFrame getFrame(){
      return frame;
  }

  public void setFrame(JFrame newFrame){
    restoreFrameState();
    frame = newFrame;
    changeFrameState();
  }

  private void changeFrameState() {
    if (frame instanceof MDIFrame) {
      MDIFrame mdiFrame = (MDIFrame)frame;
      frameAllowedMenuModifications = mdiFrame.getManager().getDocumentsModifyMenuBar();
      mdiFrame.getManager().setDocumentsModifyMenuBar(handlerControlsMenus);
    }
  }

  private void restoreFrameState() {
    if (frame instanceof MDIFrame) {
      ((MDIFrame)frame).getManager().setDocumentsModifyMenuBar(frameAllowedMenuModifications);
    }
  }

  private boolean handlerControlsMenus;

  public boolean getHandlerControlsMenus(){
    return handlerControlsMenus;
  }

  public void setHandlerControlsMenus(boolean handlerControlsMenus){
    this.handlerControlsMenus = handlerControlsMenus;
    if(handlerControlsMenus)
      changeFrameState();
    else
      restoreFrameState();
  }

  protected void initialize() throws G2AccessException{
//     GensymApplication application = GensymApplication.getApplication();
//     if (application instanceof UiApplication) {
//       // fix this: really need to be able to know when the frame changes?
//       // fix this: should we try to support java.awt.Frame?
//       frame = (JFrame)((UiApplication)application).getCurrentFrame();
//       setFrame(frame);
//     }
    menuManager = new MenuManager(twAccess);
    new GMSMenuModifier(frame, menuManager);
    initializeRPCs();
  }

  private static final Symbol _GMS_LOGIN_SESSION_ = Symbol.intern ("_GMS-LOGIN-SESSION");

  private void initializeRPCs () throws G2AccessException{
    try {
      java.lang.reflect.Method hmnMethod = 
	this.getClass().getMethod("HANDLEMENUNOTIFICATION",
				  new Class[] {Integer.TYPE,
						 Structure.class,
						 Symbol.class} );
      twAccess.registerJavaMethod(this, 
				  hmnMethod,
				  HANDLEMENUNOTIFICATION_,
				  false);
      twAccess.callRPC(_GMS_LOGIN_SESSION_,
		       new Object[] {twAccess.retrieveSession()});
    } catch (NoSuchMethodException e) {
      Trace.exception(e, i18n.getString("noHandleMenuNotificationMethod"));
      throw new NoSuchMethodError(i18n.getString("noHandleMenuNotificationMethod"));
    } 
  }
  
  public void HANDLEMENUNOTIFICATION(int menuIndex, Structure menuDescription, Symbol notificationType) throws G2AccessException {
    MenuNotificationEvent e =
      new MenuNotificationEvent(this, notificationType, menuIndex, menuDescription);
    menuManager.notifyHandleMenuNotification(e);
    // the following can be used to test error handling in the KB
    //     if (e.getID() == MenuNotificationEvent.SHOW_MENU_ON_CLIENT)
    //       throw new RuntimeException("Foo");
  }
}
