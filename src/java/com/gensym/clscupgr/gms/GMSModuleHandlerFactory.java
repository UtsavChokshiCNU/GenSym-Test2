/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   GMSModuleHandler.java 
 * 
 * 
 */ 
 

package com.gensym.clscupgr.gms;

import javax.swing.JFrame;

import com.gensym.clscupgr.ModuleHandlerFactory;
import com.gensym.clscupgr.ModuleHandler;
import com.gensym.core.GensymApplication;
import com.gensym.core.UiApplication;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.util.UnexpectedException;

public class GMSModuleHandlerFactory implements ModuleHandlerFactory {

//   private Hashtable cnxnHandlerMap = new Hashtable();

  private JFrame frameForMenus;

  /**
   * For situations in which UiApplication.getCurrentFrame is
   * not sufficient.
   * @undocumented don't expose unless customers ask
   */
  public JFrame getFrameForMenus(){
      return frameForMenus;
  }

  /**
   * @undocumented don't expose unless customers ask
   */
  public void setFrameForMenus(JFrame frameForMenus){
    this.frameForMenus = frameForMenus;
  }

  @Override
  public ModuleHandler makeModuleHandler(TwAccess connection, Symbol moduleName) {
//     ModuleHandler existingHandler =
//       (ModuleHandler)cnxnHandlerMap.get(connection);

//     if (existingHandler != null)
//       return existingHandler;

    try {
      JFrame frame = frameForMenus;
      if (frame == null) {
	GensymApplication application = GensymApplication.getApplication();
	if (application instanceof UiApplication) {
	  // fix this: really need to be able to know when the frame changes?
	  // fix this: should we try to support java.awt.Frame?
	  frame = (JFrame)((UiApplication)application).getCurrentFrame();
	}
      }
      if (frame != null) {
	ModuleHandler newHandler = new GMSModuleHandler(frame, connection);
	//     cnxnHandlerMap.put(connection, newHandler);
	return newHandler;
      } else
	return null;
    } catch (G2AccessException g2ae) {
      throw new UnexpectedException(g2ae);
    }
  }
}
