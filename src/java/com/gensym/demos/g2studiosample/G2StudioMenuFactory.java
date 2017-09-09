package com.gensym.demos.g2studiosample;

import java.awt.Color;
import java.awt.Insets;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.border.BevelBorder;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.core.MenuFactory;
import com.gensym.ui.Command;
import com.gensym.message.Resource;

import com.gensym.demos.g2studiosample.commands.BrowserCommands;
import com.gensym.demos.g2studiosample.commands.PreferencesCommands;
import com.gensym.demos.g2studiosample.commands.NavigationCommands;
import com.gensym.wksp.PaletteCommands;
import com.gensym.wksp.CreationCommands;
import com.gensym.wksp.SystemMenuChoiceCommands;
import com.gensym.uitools.inspect.InspectSessionCommands;
import com.gensym.shell.commands.ConnectionCommands;
import com.gensym.shell.commands.ExitCommands;
import com.gensym.shell.commands.CondensedG2StateCommands;
import com.gensym.shell.commands.TopLevelSystemTablesCommands;
import com.gensym.shell.commands.WorkspaceCommands;
import com.gensym.shell.commands.EditCommands;
import com.gensym.shell.commands.ViewCommands;
import com.gensym.shell.commands.ComponentVisibilityCommands;
import com.gensym.demos.g2studiosample.commands.PackagePreparationCommands;
import com.gensym.demos.g2studiosample.commands.DebuggingCommands;
import com.gensym.shell.commands.ProjectCommands;
import com.gensym.demos.g2studiosample.commands.HelpCommands;
import com.gensym.shell.commands.WorkspaceInstanceCommands;
import com.gensym.shell.commands.ZoomCommands;
import com.gensym.shell.commands.ModuleCommands;
import com.gensym.shell.commands.AlignmentCommands;
import com.gensym.shell.commands.OrderCommands;
import com.gensym.shell.commands.NudgeCommands;
import com.gensym.shell.commands.G2Commands;
import com.gensym.shell.commands.ItemCommands;
import com.gensym.shell.commands.WorkspaceAnnotationCommands;
import com.gensym.shell.commands.RotateCommands;
import com.gensym.ui.Command;
import javax.swing.SwingConstants;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ntw.util.VersionHelper;

public class G2StudioMenuFactory implements MenuFactory {
  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/g2studiosample/UiLabels");
  private RepresentationConstraints defaultMenuConstraints = 
                             new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
							   SwingConstants.LEFT, 
							   SwingConstants.CENTER, 
							   SwingConstants.RIGHT, 
							   SwingConstants.CENTER);  
  private CMenu windowMenu;
  private G2StudioCommands studioCommands;  
  protected JMenuBar workspaceDocumentMenuBar, defaultMenuBar;  
  protected Shell shell;

  public G2StudioMenuFactory(Shell shell) {
    this.shell = shell;
    this.studioCommands = shell.getG2StudioCommands();
  }
  
  @Override
  public JMenuBar getMenuBar(Object focalObject) {
    if (focalObject instanceof WorkspaceDocument)
      return createWorkspaceDocumentMenuBar();
    else
      return createDefaultMenuBar();
  }

  @Override
  public JMenu getMenu(Object focalObject) {
    if (shell.WINDOW_MENU.equals(focalObject))
      return getWindowMenu();
    else
      return null;
  }
  
  protected JMenuBar createDefaultMenuBar() {
    if (defaultMenuBar == null) {
      defaultMenuBar = new JMenuBar();
      defaultMenuBar.add (getFileMenu());    
      defaultMenuBar.add (getEditMenu());
      defaultMenuBar.add (getViewMenu());
      defaultMenuBar.add (getGoMenu());
      defaultMenuBar.add (getWkspMenu());
      defaultMenuBar.add (getG2Menu());
      defaultMenuBar.add (getToolsMenu());
      defaultMenuBar.add (getWindowMenu());
      defaultMenuBar.add (getHelpMenu());
      defaultMenuBar.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
      FontUtil.initMenuElement(defaultMenuBar, new Insets(2,0,2,5), FontUtil.sanserifPlain11);
    }
    return defaultMenuBar;
  }
  
  protected JMenuBar createWorkspaceDocumentMenuBar() {
    if (workspaceDocumentMenuBar == null) {
      workspaceDocumentMenuBar = new CMenuBar();
      workspaceDocumentMenuBar.add (getFileMenu());
      workspaceDocumentMenuBar.add (getDocumentEditMenu());
      workspaceDocumentMenuBar.add (getViewMenu ());
      workspaceDocumentMenuBar.add (getGoMenu());
      workspaceDocumentMenuBar.add (getInsertMenu());    
      workspaceDocumentMenuBar.add (getLayoutMenu());    
      workspaceDocumentMenuBar.add (getWkspMenu ());
      workspaceDocumentMenuBar.add (getG2Menu ());
      workspaceDocumentMenuBar.add (getToolsMenu ());
      workspaceDocumentMenuBar.add (getWindowMenu());
      workspaceDocumentMenuBar.add (getHelpMenu ());
      //mb.setHelpMenu(HELP_MENU);
      
      workspaceDocumentMenuBar.setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED,
								      Color.white,
								      Color.gray));          
      FontUtil.initMenuElement(workspaceDocumentMenuBar,
			       new java.awt.Insets(2,0,2,5),
			       FontUtil.sanserifPlain11);
    }
    return workspaceDocumentMenuBar;
  }  

  public CMenu getFileMenu () {
    CMenu fileMenu = new CMenu (i18ui.getString ("fileMenu"));
    fileMenu.setMnemonic(i18ui.getString("ShellFileMenuMnemonic").charAt(0));

    CMenu newMenu = new CMenu (i18ui.getString("newMenu"));
    WorkspaceCommands wkspCommand = studioCommands.getWorkspaceCommands();
    newMenu.add(wkspCommand, wkspCommand.NEW_KBWORKSPACE, defaultMenuConstraints);
    //NEW KB??? (ie clear kb and initialize a new one)(see new-project)
    //newMenu.add(cxnCommand, cxnCommands.SPAWN_G2);
    fileMenu.add(newMenu);    
    
    CMenu openMenu = new CMenu (i18ui.getString("openMenu"));
    openMenu.add (wkspCommand, wkspCommand.GET_KBWORKSPACE, defaultMenuConstraints);
    ProjectCommands projectCommands = studioCommands.getProjectCommands();
    openMenu.add(projectCommands, projectCommands.OPEN_PROJECT, defaultMenuConstraints);//change to Open KB
    ConnectionCommands cxnCommand = studioCommands.getConnectionCommands();
    openMenu.add (cxnCommand, cxnCommand.TW_CONNECT, defaultMenuConstraints);    
    fileMenu.add(openMenu);
    
    CMenu closeMenu = new CMenu (i18ui.getString("closeMenu"));
    closeMenu.add(projectCommands, projectCommands.CLOSE_PROJECT, defaultMenuConstraints);//change to Close KB
    closeMenu.add (cxnCommand, cxnCommand.TW_DISCONNECT, defaultMenuConstraints);

    fileMenu.add(closeMenu);
    
    fileMenu.addSeparator();
    fileMenu.add(projectCommands, projectCommands.SAVE_PROJECT, defaultMenuConstraints);
    fileMenu.add(projectCommands, projectCommands.SAVE_PROJECT_AS, defaultMenuConstraints);
    fileMenu.add(projectCommands, projectCommands.SAVE_PROJECT_AS_ALL_FILE, defaultMenuConstraints);
    fileMenu.addSeparator();
    CMenu modulesMenu = new CMenu(i18ui.getString("modulesMenu"));
    modulesMenu.setMnemonic(i18ui.getString("ShellModulesMenuMnemonic").charAt(0));
    ModuleCommands moduleCommands = studioCommands.getModuleCommands();    
    modulesMenu.add(moduleCommands);
    fileMenu.add(modulesMenu);
    fileMenu.addSeparator();
    WorkspaceInstanceCommands workspaceInstanceCommands = studioCommands.getWorkspaceInstanceCommands();
    fileMenu.add(workspaceInstanceCommands,workspaceInstanceCommands.PRINT_WORKSPACE, 
		 defaultMenuConstraints);
    fileMenu.addSeparator();    
    fileMenu.add(studioCommands.getExitCommands(), defaultMenuConstraints);
    fileMenu.setMargin(new Insets(2,5,2,5));
    return fileMenu;
  }

  public CMenu getEditMenu () {
    CMenu menu = new CMenu (i18ui.getString("editMenu"));
    menu.setMnemonic(i18ui.getString("ShellEditMenuMnemonic").charAt(0));    
    menu.add(studioCommands.getEditCommands(), defaultMenuConstraints);
    menu.addSeparator();
    WorkspaceInstanceCommands workspaceInstanceCommands = studioCommands.getWorkspaceInstanceCommands();    
    menu.add(workspaceInstanceCommands,workspaceInstanceCommands.SELECT_ALL_WORKSPACE_ITEMS,               
	     defaultMenuConstraints);

    //menu.addSeparator();
    //CMenu imenu = new CMenu(i18ui.getString("insert"));
    //imenu.add(creationCommands, CreationCommands.NEW_ITEM, defaultMenuConstraints);
    //menu.add(imenu);
    menu.addSeparator();
    menu.add(studioCommands.getPreferencesCommands(), defaultMenuConstraints);
    return menu;
  }

  public CMenu getG2Menu () {
    CMenu g2Menu = new CMenu (i18ui.getString ("g2Menu"));    
    g2Menu.setMnemonic(i18ui.getString("ShellG2MenuMnemonic").charAt(0));
    g2Menu.add (studioCommands.getCondensedG2StateCommands(), defaultMenuConstraints);
    g2Menu.addSeparator();    
    CMenu systemTablesMenu = new CMenu (i18ui.getString("systemTablesMenu"));
    TopLevelSystemTablesCommands topLevelSystemTablesCommands =
      new TopLevelSystemTablesCommands(shell.getCurrentFrame(), shell.getConnectionManager());
    systemTablesMenu.add(topLevelSystemTablesCommands);
    g2Menu.add(systemTablesMenu);
    g2Menu.addSeparator();
    g2Menu.add(studioCommands.getG2Commands(), defaultMenuConstraints);
    return g2Menu;
  }

  public CMenu getViewMenu () {
    CMenu viewMenu = new CMenu (i18ui.getString ("viewMenu"));
    viewMenu.setMnemonic(i18ui.getString("ShellViewMenuMnemonic").charAt(0));    
    viewMenu.add (studioCommands.getViewCommands(), defaultMenuConstraints);
    viewMenu.addSeparator();
    viewMenu.add(studioCommands.getBrowserCommands(), defaultMenuConstraints);
    viewMenu.addSeparator();
    viewMenu.add(studioCommands.getFrameVisibilityCommands(), defaultMenuConstraints);
    viewMenu.addSeparator();
    CMenu viewToolbar = new CMenu(i18ui.getString("toolBarsMenu"));
    ComponentVisibilityCommands compVisibilityCommands = studioCommands.getComponentVisibilityCommands();
    viewToolbar.add(compVisibilityCommands);
    viewMenu.add(viewToolbar);
    
    if (VersionHelper.isUsingJava2D(this.getClass())) {
      viewMenu.addSeparator();          
      viewMenu.add(studioCommands.getZoomCommands(), defaultMenuConstraints);
    }
    return viewMenu;
  }

  public CMenu getGoMenu() {
    NavigationCommands navigationCommands = studioCommands.getNavigationCommands();
    CMenu goMenu = new CMenu (i18ui.getString ("goMenu"));
    goMenu.setMnemonic(i18ui.getString("ShellGoMenuMnemonic").charAt(0));    
    goMenu.add (navigationCommands, navigationCommands.GO_HOME ,defaultMenuConstraints);
    goMenu.add (navigationCommands, navigationCommands.GO_BACK ,defaultMenuConstraints);
    goMenu.add (navigationCommands, navigationCommands.GO_FORWARD ,defaultMenuConstraints);
    goMenu.add (navigationCommands, navigationCommands.STOP_DOWNLOAD ,defaultMenuConstraints);    
    return goMenu;
  }
  
  public CMenu getWkspMenu () {
    WorkspaceCommands wkspCommand = studioCommands.getWorkspaceCommands();
    WorkspaceInstanceCommands workspaceInstanceCommands
      = studioCommands.getWorkspaceInstanceCommands();            
    CMenu wkspMenu = new CMenu (i18ui.getString ("wkspMenu"));
    wkspMenu.setMnemonic(i18ui.getString("ShellWorkspaceMenuMnemonic").charAt(0));
    wkspMenu.add (wkspCommand, wkspCommand.GET_KBWORKSPACE, defaultMenuConstraints);
    wkspMenu.add (wkspCommand, wkspCommand.NEW_KBWORKSPACE, defaultMenuConstraints);
    wkspMenu.addSeparator ();
    wkspMenu.add(workspaceInstanceCommands,workspaceInstanceCommands.SHRINK_WRAP_WORKSPACE,
		 defaultMenuConstraints);
    wkspMenu.addSeparator();
    wkspMenu.add(workspaceInstanceCommands,workspaceInstanceCommands.ENABLE_WORKSPACE,
		 defaultMenuConstraints);
    wkspMenu.add(workspaceInstanceCommands,workspaceInstanceCommands.DISABLE_WORKSPACE,
		 defaultMenuConstraints);
    wkspMenu.addSeparator();
    wkspMenu.add(workspaceInstanceCommands,workspaceInstanceCommands.DELETE_WORKSPACE,
		 defaultMenuConstraints);
    wkspMenu.addSeparator();    
    wkspMenu.add(workspaceInstanceCommands,workspaceInstanceCommands.WORKSPACE_PROPERTIES,
		 defaultMenuConstraints);    
    return wkspMenu;
  }

  public CMenu getWindowMenu () {
    if (windowMenu == null) {
      windowMenu = new CMenu (i18ui.getString ("windowMenu"));
      windowMenu.setMnemonic(i18ui.getString("ShellWindowMenuMnemonic").charAt(0));

      NavigationCommands navigationCommands = studioCommands.getNavigationCommands();
      windowMenu.add(navigationCommands, navigationCommands.NEXT_WINDOW, defaultMenuConstraints);    
      windowMenu.add(navigationCommands, navigationCommands.PREVIOUS_WINDOW, defaultMenuConstraints);
      windowMenu.addSeparator();    
      windowMenu.add(studioCommands.getTilingCommand(), defaultMenuConstraints);
    }
    return windowMenu;
  }

  public CMenu getAlignmentMenu() {
    CMenu menu = new CMenu (i18ui.getString("alignmentMenu"));
    menu.setMnemonic(i18ui.getString("ShellAlignMenuMnemonic").charAt(0));                  
    menu.add(studioCommands.getAlignmentCommands(),defaultMenuConstraints);
    return menu;
  }
    
  public CMenu getNudgeMenu() {
    CMenu menu = new CMenu (i18ui.getString("nudgeMenu"));
    menu.setMnemonic(i18ui.getString("ShellNudgeMenuMnemonic").charAt(0));              
    menu.add(studioCommands.getNudgeCommands(), defaultMenuConstraints);
    return menu;
  }
  
  public CMenu getToolsMenu () {
    CMenu toolsMenu = new CMenu (i18ui.getString ("toolsMenu"));
    toolsMenu.setMnemonic(i18ui.getString("ShellToolsMenuMnemonic").charAt(0));        
    toolsMenu.add(studioCommands.getInspectSessionCommands(), defaultMenuConstraints);
    toolsMenu.addSeparator();        
    toolsMenu.add(studioCommands.getPackagePreparationCommands(), defaultMenuConstraints);
    toolsMenu.addSeparator();
    CMenu menu = new CMenu(i18ui.getString("customize"));
    PaletteCommands paletteCommands = studioCommands.getPaletteCommands();
    menu.add(paletteCommands, paletteCommands.CLASSES, defaultMenuConstraints);
    WorkspaceAnnotationCommands workspaceAnnotationCommands
      = studioCommands.getWorkspaceAnnotationCommands();
    menu.add(workspaceAnnotationCommands,
	     workspaceAnnotationCommands.EDIT_ANNOTATIONS,
	     defaultMenuConstraints);
    toolsMenu.add(menu);
    return toolsMenu;
  }

  public CMenu getHelpMenu () {
    CMenu helpMenu = new CMenu (i18ui.getString ("helpMenu"));
    helpMenu.setMnemonic(i18ui.getString("ShellHelpMenuMnemonic").charAt(0));                    
    helpMenu.add (studioCommands.getHelpCommands(), defaultMenuConstraints);
    return helpMenu;
  }

  public CMenu getInsertMenu () {
    CMenu menu = new CMenu (i18ui.getString("insertMenu"));
    menu.setMnemonic(i18ui.getString("ShellWorkspaceInsertMenuMnemonic").charAt(0));
    menu.add(studioCommands.getCreationCommands(), CreationCommands.NEW_ITEM, defaultMenuConstraints);
    
    return menu;
  }
  
  public CMenu getDocumentEditMenu() {
    CMenu editMenu = new CMenu (i18ui.getString("editMenu"));
    editMenu.setMnemonic(i18ui.getString("ShellEditMenuMnemonic").charAt(0));    
    editMenu.add(studioCommands.getEditCommands(), defaultMenuConstraints);
    editMenu.addSeparator();
    editMenu.add(studioCommands.getWorkspaceInstanceCommands(),
		 WorkspaceInstanceCommands.SELECT_ALL_WORKSPACE_ITEMS,               
		 defaultMenuConstraints);
    editMenu.addSeparator();
    ItemCommands itemCommands = studioCommands.getItemCommands();
    editMenu.add(itemCommands, ItemCommands.DELETE_SELECTION, defaultMenuConstraints);
    editMenu.addSeparator();
    editMenu.add(itemCommands, ItemCommands.ENABLE_SELECTION, defaultMenuConstraints);
    editMenu.add(itemCommands, ItemCommands.DISABLE_SELECTION, defaultMenuConstraints);
    editMenu.addSeparator();

    editMenu.add(itemCommands, ItemCommands.DESCRIBE, defaultMenuConstraints);
    editMenu.add(itemCommands, ItemCommands.DESCRIBE_CONFIGURATION, defaultMenuConstraints);
    editMenu.addSeparator();
    editMenu.add(itemCommands, ItemCommands.EDIT_ITEM_TEXT, defaultMenuConstraints);
    editMenu.add(itemCommands, ItemCommands.COLOR, defaultMenuConstraints);
    editMenu.add(itemCommands, ItemCommands.FONT_SIZE, defaultMenuConstraints);
    editMenu.add(itemCommands, ItemCommands.ITEM_PROPERTIES, defaultMenuConstraints);
    editMenu.addSeparator();    
    editMenu.add(studioCommands.getPreferencesCommands(), defaultMenuConstraints);
    
    return editMenu;
  }

  public CMenu getReflectMenu() {
    CMenu menu = new CMenu (i18ui.getString("reflectMenu"));
    menu.setMnemonic(i18ui.getString("ShellReflectMenuMnemonic").charAt(0));
    RotateCommands rotateCommands = studioCommands.getRotateCommands();
    menu.add (rotateCommands, RotateCommands.FLIP_HORIZONTAL, defaultMenuConstraints);
    menu.add (rotateCommands, RotateCommands.FLIP_VERTICAL, defaultMenuConstraints);
    return menu;
  }

  public CMenu getLayoutMenu() {
    CMenu menu = new CMenu (i18ui.getString("layoutMenu"));
    menu.setMnemonic(i18ui.getString("ShellLayoutMenuMnemonic").charAt(0));    
    menu.add(studioCommands.getOrderCommands(), defaultMenuConstraints);
    menu.addSeparator();
    menu.add(getReflectMenu());
    menu.add(getRotateMenu());
    menu.addSeparator();
    menu.add(getAlignmentMenu());
    menu.add(getNudgeMenu());
    return menu;
  }
  
  public CMenu getRotateMenu() {
    CMenu menu = new CMenu (i18ui.getString("rotateMenu"));
    menu.setMnemonic(i18ui.getString("ShellRotateMenuMnemonic").charAt(0));
    RotateCommands rotateCommands = studioCommands.getRotateCommands();
    menu.add (rotateCommands, RotateCommands.ROTATE_90_CLOCKWISE, defaultMenuConstraints);
    menu.add (rotateCommands, RotateCommands.ROTATE_90_COUNTER_CLOCKWISE, defaultMenuConstraints);
    menu.add (rotateCommands, RotateCommands.ROTATE_180_DEGREES, defaultMenuConstraints);
    return menu;
  }
  
}
