/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DlgTestApp.java
 *
 */
package com.gensym.demos.standarddialogs;

import com.gensym.mdi.MDIFrame;
import com.gensym.core.UiApplication;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import javax.swing.UIManager;

/**
 * DlgTestApp is an application shell that demonstrates the usage of many
 * of the dialogs in com.gensym.dlg. The menus for DlgTestApp are generated
 * from com.gensym.demos.standarddialogs.DlgCommand. DlgCommand is the class
 * that actually handles the displaying and dismissing of the dialogs in the
 * demo.
 */
public class DlgTestApp extends UiApplication {
  private MDIFrame frame;
  private CMenuBar menuBar;

  public DlgTestApp(String[] cmdLineArgs) {
    super(cmdLineArgs, true);
    createDlgTestApp();
  }

  private void createDlgTestApp() {
    frame = createFrame("Dlg Test Application");
    // set the current frame in UiApplication
    setCurrentFrame(frame);
    createUiComponents();
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

  private CMenuBar createMenuBar(){
    CMenuBar menu = new CMenuBar();
    menu.add(createDlgMenu());
    menu.add(createHelpMenu());
    return menu;
  }

  private CMenu createDlgMenu() {
    CMenu menu = new CMenu("Dialogs");
    menu.add(new DlgCommand(frame));
    return menu;
  }

  private CMenu createHelpMenu() {
    CMenu menu = new CMenu("Help");
    menu.add(new HelpCommands(frame));
    return menu;
  }

  public static void main(String[] cmdLineArgs){
    // Set the look and feel to be defined by the client's system
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
