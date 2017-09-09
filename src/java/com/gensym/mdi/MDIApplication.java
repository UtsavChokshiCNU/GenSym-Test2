/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIApplication.java
 *
 */
package com.gensym.mdi;

import com.gensym.core.MenuFactory;
import com.gensym.core.ToolBarFactory;
import javax.swing.JMenuBar;
import java.awt.Component;

/**
 * A Class that can be used as the parent of all MDI applications.
 * It currently provides nothing, but will be extended later as we
 * spec out the requires for an MDI application.
 */
public abstract class MDIApplication extends com.gensym.core.UiApplication {

  /**
   * @undocumented
   */
  protected MDIApplication (String[] commandLine, boolean isMultipleFrames) {
    super(commandLine, isMultipleFrames);
  }

  protected void updateMenusForConnection(Object connection, boolean updateDocuments) {
    MenuFactory menuFactory = getMenuFactory(connection);
    JMenuBar applnMenuBar = menuFactory.getMenuBar(null);
    MDIFrame mdiFrame = (MDIFrame)getCurrentFrame();
    mdiFrame.setDefaultMenuBar(applnMenuBar, mdiFrame.getDefaultWindowMenu());
    if (updateDocuments) {
      MDIDocument[]docs = mdiFrame.getManager().getDocuments();
      int count = docs.length;
      for (int i=0;i<count;i++) {
	MDIDocument doc = docs[i];
	doc.setDocumentMenuBar(menuFactory.getMenuBar(doc),doc.getWindowMenu());
      }
    }
  }

  protected void updateToolBarsForConnection(Object connection, boolean updateDocuments) {
    ToolBarFactory toolBarFactory = getToolBarFactory(connection);
    Component toolBarComponent = toolBarFactory.getToolBarComponent(this);
    MDIFrame mdiFrame = (MDIFrame)getCurrentFrame();
    mdiFrame.setDefaultToolBarPanel((MDIToolBarPanel)toolBarComponent);//cast???
    if (updateDocuments) {
      MDIDocument[]docs = mdiFrame.getManager().getDocuments();
      int count = docs.length;
      for (int i=0;i<count;i++) {
	MDIDocument doc = docs[i];
	doc.setToolBarPanel((MDIToolBarPanel)toolBarFactory.getToolBarComponent(doc));
      }
    }
  }  
}
