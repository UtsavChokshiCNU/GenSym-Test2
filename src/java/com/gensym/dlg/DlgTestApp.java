/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DlgTestApp.java
 *
 */
package com.gensym.dlg;

import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.util.UiApplication;
import com.gensym.ui.Command;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.sun.java.swing.UIManager;

public class DlgTestApp extends UiApplication {
  private MDIFrame frame;
  private CMenuBar menuBar;

  private Command dlgHandler;

  public DlgTestApp(String[] cmdLineArgs) {
    super(cmdLineArgs, true);
    createDlgTestApp();
  }

  private void createDlgTestApp() {
    frame = createFrame("Dialog Test App");
    setCurrentFrame(frame);

    createUiComponents();

    StandardDialog.registerFrame(frame);
    registerFrameWithDialogManager(frame);
  }

  private void registerFrameWithDialogManager(MDIFrame frame) {
    com.gensym.dlgruntime.DialogManager.registerFrame(frame);
    com.gensym.dlgruntime.DefaultDialogLauncher.registerFrame(frame);
  }

  private void createUiComponents() {
    frame.setDefaultMenuBar(menuBar = createMenuBar());
  }

  private MDIFrame createFrame(String title) {
    MDIFrame frame =  new MDIFrame(title);
    return frame;
  }


  protected CMenuBar createMenuBar(){
    CMenuBar menu = new CMenuBar();
    menu.add(createDlgMenu());
    return menu;
  }

  private CMenu createDlgMenu() {
    CMenu menu = new CMenu("Dialogs");

    if (dlgHandler == null) 
      dlgHandler = new DlgCommand(frame);

    menu.add(dlgHandler);
    return menu;
  }

  public static void main(String[] cmdLineArgs){
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    DlgTestApp app = new DlgTestApp(cmdLineArgs);
    app.frame.setVisible(true);
  }
}
