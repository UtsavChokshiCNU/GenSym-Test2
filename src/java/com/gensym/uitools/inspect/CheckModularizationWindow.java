package com.gensym.uitools.inspect;

import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import java.awt.Window;
import javax.swing.SwingConstants;

public class CheckModularizationWindow extends InspectWindow {
  
  public CheckModularizationWindow(Window window) {
    super(window);
    setPrefix(InspectSession.CHECK_MODULARIZATION);
    getControlPanel().setVisible(false);
    getInspectSessionViewer().setStatusBarVisible(false);
  }

  @Override
  protected CMenuBar createMainMenu(Window window,
				    InspectItemCommands inspectItemCommands,
				    InspectSessionViewer sessionViewer)
  {
    sessionViewer.getTable().setTableHeader(null);
    RepresentationConstraints menuConstraints = 
      new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				    SwingConstants.LEFT, 
				    SwingConstants.CENTER, 
				    SwingConstants.RIGHT, 
				    SwingConstants.CENTER);    
    CMenuBar applnMenuBar = new com.gensym.ui.menu.CMenuBar();
    CMenu fileMenu = new CMenu(i18ui.getString ("file"));
    fileMenu.setMnemonic(i18ui.getString("FileMenuMnemonic").charAt(0));
    InspectMainMenuCommands inspectMainMenuCommands =
      new InspectMainMenuCommands(window, this);
    fileMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.EXIT,
		 menuConstraints);
    applnMenuBar.add(fileMenu);
    CMenu editMenu = new CMenu(i18ui.getString ("edit"));
    editMenu.setMnemonic(i18ui.getString("EditMenuMnemonic").charAt(0));
    editMenu.add(inspectItemCommands, menuConstraints);
    editMenu.addSeparator();
    editMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.SELECT_ALL,
		 menuConstraints);
    editMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.INVERT_SELECTION);
    applnMenuBar.add(editMenu);
    CMenu helpMenu = new CMenu(i18ui.getString ("help"));
    helpMenu.setMnemonic(i18ui.getString("HelpMenuMnemonic").charAt(0));
    helpMenu.add(inspectMainMenuCommands, inspectMainMenuCommands.ABOUT);
    applnMenuBar.add(helpMenu);
    return applnMenuBar;
  }

}
