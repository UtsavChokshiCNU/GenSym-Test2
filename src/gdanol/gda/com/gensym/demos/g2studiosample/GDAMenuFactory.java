package com.gensym.demos.g2studiosample;

import java.awt.Color;
import java.awt.Insets;
import javax.swing.JMenuBar;
import javax.swing.border.BevelBorder;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import com.gensym.shell.util.WorkspaceDocument;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.ModuleInformation;
import com.gensym.core.UiApplication;
import com.gensym.core.MenuFactory;

import com.gensym.message.Resource;
import com.gensym.ui.RepresentationConstraints;
import javax.swing.SwingConstants;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.ntw.TwGateway;

import java.util.ResourceBundle;
import com.gensym.message.MessageKey;
import com.gensym.gda.dialogs.gdaDialogManagerFactory;
import com.gensym.gda.dialogs.gdaDialogManager;
import com.gensym.gda.util.GfrCommunicationManager;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.classes.Item;
import com.gensym.gda.commands.*;
import com.gensym.gda.queues.ShowQueuesCommand;

public class GDAMenuFactory extends G2StudioMenuFactory {

  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/g2studiosample/GDALabels");
  private RepresentationConstraints defaultMenuConstraints = 
                             new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
							   SwingConstants.LEFT, 
							   SwingConstants.CENTER, 
							   SwingConstants.RIGHT, 
							   SwingConstants.CENTER);
  ResetAllBlocksCommand resetAllBLocksHandler;
  EnableDataInputCommand enabledataInputHandler;
  AnimateCommand animateHandler;
  ShowApplicationsCommand showApplicationsHandler;
  PalettesCommands palettesHandler;
  ShowQueuesCommand queuesHandler;
  PreferencesCommand preferencesHandler;
  
  public GDAMenuFactory(Shell shell) {
    super(shell);
  }

  public static void register(ModuleInformation module, UiApplication shell) {
    if (shell instanceof Shell) {
      Shell s = (Shell)shell;
      GDAMenuFactory menuFactory = new GDAMenuFactory(s);
      menuFactory.setupFields();
      gdaDialogManagerFactory dialogFactory = new gdaDialogManagerFactory();
      //com.gensym.ntw.TwGateway.setDialogManagerFactory(dialogFactory); 
      //                  This would set it for future connections, which we shouldn't be doing.
      TwAccess connection = s.getConnectionManager().getCurrentConnection();
      gdaDialogManager dialogManager = (gdaDialogManager)dialogFactory.makeDialogManager(connection);
      dialogManager.addDialogResource(ResourceBundle.getBundle("com.gensym.gda.dialogs.Dialogs",
							       Resource.getDefaultLocale(),
							       GDAMenuFactory.class.getClassLoader()));
      TwGateway gateway = (TwGateway) connection;
      gateway.setDialogManager(dialogManager);
      menuFactory.registerLocalRPCs(connection);
      shell.setMenuFactory(((ImplAccess)module).getContext(),menuFactory);
    }
  }
  public JMenuBar getMenuBar(Object focalObject) {
    if (focalObject instanceof WorkspaceDocument)
      return createWorkspaceDocumentMenuBar();
    else
      return createDefaultMenuBar();
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

      defaultMenuBar.add (createGDAMenu());

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
      workspaceDocumentMenuBar.add (getEditMenu());
      workspaceDocumentMenuBar.add (getViewMenu ());
      workspaceDocumentMenuBar.add (getGoMenu());
      workspaceDocumentMenuBar.add (getInsertMenu());    
      workspaceDocumentMenuBar.add (getLayoutMenu());
      workspaceDocumentMenuBar.add (getWkspMenu ());

      workspaceDocumentMenuBar.add (createGDAMenu());
      
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
  CMenu createGDAMenu() {
    CMenu gdaMenu = new CMenu (i18ui.getString("ShellGDAMenu"));
    gdaMenu.setMnemonic(i18ui.getString("ShellGDAMenuMnemonic").charAt(0));
    gdaMenu.add(resetAllBLocksHandler = new ResetAllBlocksCommand(shell), defaultMenuConstraints);
    gdaMenu.add(enabledataInputHandler = new EnableDataInputCommand(shell), defaultMenuConstraints);
    gdaMenu.add(animateHandler=new AnimateCommand(shell), defaultMenuConstraints);
    gdaMenu.add(showApplicationsHandler=new ShowApplicationsCommand(shell), defaultMenuConstraints);
    gdaMenu.addSeparator();
    gdaMenu.add(palettesHandler, defaultMenuConstraints);
    gdaMenu.add(queuesHandler, defaultMenuConstraints);
    //gdaMenu.add(palettesHandler=new PalettesCommands(shell), defaultMenuConstraints);
    gdaMenu.addSeparator();
    gdaMenu.add(preferencesHandler=new PreferencesCommand(shell), defaultMenuConstraints);
    return gdaMenu;
  }

  private void setupFields () {
    palettesHandler = new PalettesCommands(shell);
    queuesHandler = new ShowQueuesCommand(shell);
  }

  void registerLocalRPCs(TwAccess connection) {
    connection.registerJavaMethod(this, "gdlLaunchDialog", GDL_LAUNCH_DIALOG_);
    connection.registerJavaMethod(this, "gdlPromptForValueFromList", GDL_PROMPT_FOR_VALUE_FROM_LIST_);
    connection.registerJavaMethod(this, "gdlPromptForValue", GDL_PROMPT_FOR_VALUE_);
    connection.registerJavaMethod(this, "gdlHandleCommunication", GDL_HANDLE_COMMUNICATION_IN_TW2_);
    connection.registerJavaMethod(this, "gdlShowPathTable", GDL_SHOW_PATH_TABLE_);
  }

  public void gdlHandleCommunication(Item gfrComm, String message, Sequence buttons) {
    GfrCommunicationManager.handleCommunication(gfrComm, message, buttons);
  }
  
  public Sequence gdlPromptForValueFromList(String title,  
					    String prompt, int defaultIndex, Sequence initialValues) {
     		
    TwAccess connection = shell.getConnectionManager().getCurrentConnection();
    return ((gdaDialogManager)connection.getDialogManager()).promptForValueFromList(
										    shell.getCurrentFrame(), title,  prompt, defaultIndex, initialValues);
  }
     	
  public Sequence gdlPromptForValue(String prompt, 
				    String initialValue, Symbol formatSpec) {
    
    TwAccess connection = shell.getConnectionManager().getCurrentConnection();
    
    return ((gdaDialogManager)connection.getDialogManager()).promptForValue(
									    shell.getCurrentFrame(), prompt, initialValue, formatSpec, connection);
  }
 
  public void gdlShowPathTable(String title, 
			       com.gensym.classes.modules.gdluisup.GdlPathItemEventManager manager,
			       Sequence attrNames, Sequence initVals){
    TwAccess connection = shell.getConnectionManager().getCurrentConnection();
    ((gdaDialogManager)connection.getDialogManager()).
      showPathTable(shell.getCurrentFrame(), title, manager, attrNames, initVals);
  }
 
  public void gdlLaunchDialog(Structure additionalData) {
 		
    TwAccess connection = shell.getConnectionManager().getCurrentConnection();
    ((gdaDialogManager)connection.getDialogManager()).
      startDialog(shell.getCurrentFrame(), additionalData, connection);
  }
 
  protected GfrCommunicationManager gfrCommunicationManager;
 
  private final static Symbol GDL_LAUNCH_DIALOG_ = Symbol.intern("_GDL-LAUNCH-DIALOG");
  private final static Symbol GDL_PROMPT_FOR_VALUE_FROM_LIST_ = 
  Symbol.intern("GDL-PROMPT-FOR-VALUE-FROM-LIST-IN-TW2");
  private final static Symbol GDL_PROMPT_FOR_VALUE_ = 
  Symbol.intern("GDL-PROMPT-FOR-VALUE-IN-TW2");
  private final static Symbol GDL_HANDLE_COMMUNICATION_IN_TW2_ =
  Symbol.intern("GDL-HANDLE-COMMUNICATION-IN-TW2");
  private final static Symbol GDL_SHOW_PATH_TABLE_ =
  Symbol.intern("GDL-SHOW-PATH-TABLE");
}







