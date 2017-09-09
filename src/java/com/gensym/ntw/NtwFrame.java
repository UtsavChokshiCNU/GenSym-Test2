
package com.gensym.ntw;

import java.awt.*;
import java.util.*;
import com.gensym.dlg.*;
import com.gensym.oldmdi.*;
import com.gensym.dlg.*;
import com.gensym.jgi.*;
//import com.gensym.jgi.SimpleChart;
//import com.gensym.jgi.ImprovedChart;
import com.gensym.wksp.*;
import com.gensym.wksp.BeanElement;
import com.gensym.message.Resource;
import com.gensym.message.*;
import com.gensym.util.Structure;
import com.gensym.message.*;
import com.gensym.util.Symbol;
import com.gensym.message.*;
import com.gensym.jgi.download.StubClassLoader;
import com.gensym.message.*;
import com.gensym.message.Trace;
import com.gensym.message.*;
// import com.gensym.controls.BeanPanel;
import java.lang.Object;
import com.gensym.draw.ViewScrollbar;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;

public class NtwFrame extends MDIFrame 
  implements StandardDialogClient, WorkspaceShowingListener
  
{
  
  // Knows about Tw specific menus and stuff..
  Telewindows application;
  private static MenuItem quitItem, openXnItem, closeItem, switchItem, newWkspItem,
    newPanelItem, getNamedWkspItem, chartItem, newChartItem, newControlItem, 
    jgiDebugItem, traceOnItem, stubItem, testItem, traceExOnItem,
    genOnItem, genOffItem, genAutoItem,
    subscribeShowingItem, unsubscribeShowingItem, 
    editItem, cutItem, copyItem, pasteItem, cloneItem, deleteItem,
    selectAllItems, getUilDialogItem, cascadeItem, tileHorizItem, tileVertItem,
    getBeansDialogItem, startG2Item, pauseG2Item, resetG2Item;

  private String lastConnectedURL = "", lastConnectedHost = "localhost", lastConnectedPort = "1111";

  private static MDICheckboxMenuItem activeGenModeItem;
    
  private static MDIMenu windowMenu;

  private static final Resource i18n =
  (Resource)Resource.getBundle("com.gensym.resources.MenuStrings",
				   Telewindows.getCurrentLocale());
  private static final MDIMenu MODULEMENU       = createModuleMenu ();
  private static final MDIMenu SAVEALLMENU      = createSaveAllMenu ();
  private static final MDIMenu PREFERENCESMENU  = createPreferencesMenu ();
  private static final MDIMenu FILEMENU         = createFileMenu ();
  private static final MDIMenu EDITMENU		= createEditMenu ();
  private static final MDIMenu VIEWMENU		= createViewMenu ();
  private static final MDIMenu FORMATMENU	= createFormatMenu ();
  private static final MDIMenu ALIGNMENU        = createAlignMenu ();
  private static final MDIMenu DISTRIBUTEMENU   = createDistributeMenu ();
  private static final MDIMenu ROTATEFLIPMENU   = createRotateFlipMenu ();
  private static final MDIMenu RESHAPEMENU      = createReshapeMenu ();
  private static final MDIMenu LAYOUTMENU	= createLayoutMenu ();
  private static final MDIMenu TOOLSMENU	= createToolsMenu ();
  private static final MDIMenu RUNOPTIONSMENU   = createRunOptionsMenu ();
  private static final MDIMenu G2MENU		= createG2Menu ();
  private static final MDIMenu INSERTMENU       = createInsertMenu ();
  private static final MDIMenu WINDOWMENU       = createWindowMenu ();
  private static final MDIMenu DEMOMENU		= createDemoMenu ();
  private static final MDIMenu DEBUGMENU        = createDebugMenu ();
  private static final MDIMenu HELPMENU		= createHelpMenu ();
  private static BeanElement beano = null;

  static MDIMenu createModuleMenu () {
		
    MDIMenu moduleMenu = new MDIMenu ("Modules", false);
    
    moduleMenu.add (i18n.getString("File_Modules_NewModule"));
    moduleMenu.add (i18n.getString("File_Modules_MergeModule"));
    moduleMenu.add (i18n.getString("File_Modules_EditModule"));
    moduleMenu.addSeparator();
    moduleMenu.add (i18n.getString("File_Modules_DeleteModule"));
    moduleMenu.addSeparator();
    moduleMenu.add (i18n.getString("File_Modules_CheckModularization"));
    
    return moduleMenu;
  }
  
  static MDIMenu createSaveAllMenu () {
    
    MDIMenu saveAllMenu = new MDIMenu
      (i18n.getString("File_SaveAll"), false);
    
    saveAllMenu.add (i18n.getString("File_SaveAll_AllModules"));
    saveAllMenu.add (i18n.getString("File_SaveAll_AllModulesInOneFile"));
    
    return saveAllMenu;
  }
  
  static MDIMenu createPreferencesMenu () {
    
    MDIMenu preferencesMenu = new MDIMenu (i18n.getString("File_Preferences"),
					   false);
    
    preferencesMenu.add (i18n.getString("File_Preferences_KBPreferences"));
    preferencesMenu.add (i18n.getString("File_Preferences_UserPreferences"));
    return preferencesMenu;
  }

  static MDIMenu createFileMenu () {
    MDIMenu fileMenu = new MDIMenu(i18n.getString("File"), false);
    
    fileMenu.add (openXnItem = new MDIMenuItem (i18n.getString("File_TwConnect")));
    fileMenu.add (i18n.getString("File_NewKBApplication"));
    fileMenu.addSeparator();
    fileMenu.add (i18n.getString("File_OpenKBApplication"));
    fileMenu.add ((MDIMenu)MODULEMENU.clone());
    fileMenu.add (i18n.getString("File_LoadAttributeFile"));
    fileMenu.addSeparator();
    fileMenu.add (i18n.getString("File_Save"));
    fileMenu.add (i18n.getString("File_SaveAs"));
    fileMenu.add ((MDIMenu)SAVEALLMENU.clone());
    fileMenu.addSeparator();
    fileMenu.add (i18n.getString("File_SaveSnapshot"));
    fileMenu.add (i18n.getString("File_WarmbootFromSnapshot"));
    fileMenu.addSeparator();
    fileMenu.add(getNamedWkspItem =
		 new MDIMenuItem(i18n.getString("File_GetWorkspace")));
    fileMenu.add(newWkspItem =
		 new MDIMenuItem (i18n.getString("File_NewWorkspace")));
    fileMenu.add(newPanelItem =
		 new MDIMenuItem (i18n.getString("File_NewPanel")));
    fileMenu.add(switchItem =
		 new MDIMenuItem(i18n.getString("File_Switch")));
    fileMenu.addSeparator();
    fileMenu.add ((MDIMenu)PREFERENCESMENU.clone());
    fileMenu.addSeparator();
    fileMenu.add (i18n.getString("File_CloseKBApplication"));
    fileMenu.add (i18n.getString("File_ShutDownG2"));
    fileMenu.add(quitItem = new MDIMenuItem(i18n.getString("File_ExitTWSession")));
    
    return fileMenu;
  }
  
  static MDIMenu createEditMenu () {
    MDIMenu editMenu = new MDIMenu (i18n.getString("Edit"), false);
    
    editMenu.add (i18n.getString("Edit_Undo"));
    editMenu.addSeparator();
    editMenu.add (cutItem = new MDIMenuItem(i18n.getString("Edit_Cut")));
    editMenu.add (copyItem = new MDIMenuItem(i18n.getString("Edit_Copy")));
    editMenu.add (pasteItem = new MDIMenuItem(i18n.getString("Edit_Paste")));
    editMenu.add (cloneItem = new MDIMenuItem(i18n.getString("Edit_Clone")));
    editMenu.add (deleteItem = new MDIMenuItem(i18n.getString("Edit_Delete")));
    editMenu.add (selectAllItems = new MDIMenuItem(i18n.getString("Edit_SelectAll")));
    editMenu.addSeparator();
    editMenu.add (i18n.getString("Edit_Find"));
    editMenu.add (i18n.getString("Edit_Replace"));
    editMenu.add (i18n.getString("Edit_GoTo"));
    editMenu.addSeparator();
    editMenu.add (i18n.getString("Edit_Scrapbook"));
    editMenu.add (editItem = new MDIMenuItem ("Object..."));
    return editMenu;
  }
  
  static MDIMenu createViewMenu () {
    MDIMenu toolbarsMenu =
      new MDIMenu (i18n.getString("View_Toolbars"), false);
    
    toolbarsMenu.add (i18n.getString("View_Toolbars_G2"));
    toolbarsMenu.add (i18n.getString("View_Toolbars_Format"));
    toolbarsMenu.add (i18n.getString("View_Toolbars_Layout"));
    toolbarsMenu.add (i18n.getString("View_Toolbars_Tools")); 
    
    MDIMenu viewMenu = new MDIMenu ("View", false);
    
    viewMenu.add (i18n.getString("View_TopLevelWorkspaces"));
    viewMenu.add (toolbarsMenu);
    viewMenu.add (i18n.getString("View_Palettes"));
    viewMenu.add (i18n.getString("View_StatusBar"));
    viewMenu.addSeparator();
    viewMenu.add (i18n.getString("View_Logbook"));
    viewMenu.add (i18n.getString("View_MessageBoard"));
    viewMenu.addSeparator();
    viewMenu.add (i18n.getString("View_Zoom"));
    viewMenu.add (i18n.getString("View_ShowGrid"));
    
    return viewMenu;
  }
  
  static MDIMenu createFormatMenu () {
    MDIMenu formatMenu = new MDIMenu (i18n.getString("Format"), false);
    
    formatMenu.add (i18n.getString("Format_Color"));
    formatMenu.add (i18n.getString("Format_LineStyle"));
    formatMenu.add (i18n.getString("Format_FillStyle"));
    formatMenu.add (i18n.getString("Format_DropShadow"));
    formatMenu.add (i18n.getString("Format_Font"));

    return formatMenu;
  }
  
  static MDIMenu createAlignMenu () {
    MDIMenu alignMenu = new MDIMenu (i18n.getString("Layout_Align"), false);

    alignMenu.add (i18n.getString("Layout_Align_Left"));
    alignMenu.add (i18n.getString("Layout_Align_Right"));
    alignMenu.add (i18n.getString("Layout_Align_Top"));
    alignMenu.add (i18n.getString("Layout_Align_Bottom"));
    alignMenu.addSeparator();
    alignMenu.add (i18n.getString("Layout_Align_HorizontalCenter"));
    alignMenu.add (i18n.getString("Layout_Align_VerticalCenter"));
	
    return alignMenu;
  }

  static MDIMenu createDistributeMenu () {
    MDIMenu distributeMenu = new MDIMenu (i18n.getString("Layout_Distribute"), false);

    distributeMenu.add (i18n.getString("Layout_Distribute_DistributeHorizontally"));
    distributeMenu.add (i18n.getString("Layout_Distribute_DistributeVertically"));

    return distributeMenu;
  }

  static MDIMenu createRotateFlipMenu () {
    MDIMenu rotateFlipMenu = new MDIMenu (i18n.getString("Layout_RotateFlip"), false);

    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_RotateAroundObjectCenter"));
    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_SelectCenterOfRotation"));
    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_SpecifyRotation"));
    rotateFlipMenu.addSeparator();
    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_FlipHorizontally"));
    rotateFlipMenu.add (i18n.getString("Layout_RotateFlip_FlipVertically"));

    return rotateFlipMenu;
  }

  static MDIMenu createReshapeMenu () {

    MDIMenu reshapeMenu = new MDIMenu (i18n.getString("Layout_Reshape"), false);
    reshapeMenu.add (i18n.getString("Layout_Reshape_MoveControlPoints"));
    reshapeMenu.add (i18n.getString("Layout_Reshape_AddControlPoints"));
    reshapeMenu.add (i18n.getString("Layout_Reshape_DeleteControlPoints")); 

    return reshapeMenu;
  }

  static MDIMenu createLayoutMenu () {
    MDIMenu layoutMenu = new MDIMenu (i18n.getString("Layout"), false);

    layoutMenu.add (i18n.getString("Layout_Group"));
    layoutMenu.add (i18n.getString("Layout_Ungroup"));
    layoutMenu.addSeparator();
    layoutMenu.add (i18n.getString("Layout_LiftToTop"));
    layoutMenu.add (i18n.getString("Layout_DropToBottom"));
    layoutMenu.add (i18n.getString("Layout_LiftOneLayer"));
    layoutMenu.add (i18n.getString("Layout_DropOneLayer"));
    layoutMenu.addSeparator();
    layoutMenu.add ((MDIMenu)ALIGNMENU.clone());
    layoutMenu.add ((MDIMenu)DISTRIBUTEMENU.clone());
    layoutMenu.add ((MDIMenu)ROTATEFLIPMENU.clone());
    layoutMenu.add (i18n.getString("Layout_Scale"));
    layoutMenu.add ((MDIMenu)createReshapeMenu());
    layoutMenu.addSeparator();
    layoutMenu.add (i18n.getString("Layout_GridSettings"));

    return layoutMenu;
  }
  
  static MDIMenu createToolsMenu () {
    MDIMenu toolsMenu = new MDIMenu (i18n.getString("Tools"), false);
    toolsMenu.add (i18n.getString("Tools_Inspector"));
    toolsMenu.add (i18n.getString("Tools_ClassHierarchy"));
    toolsMenu.add (i18n.getString("Tools_ModuleHierarchy"));
    toolsMenu.add (i18n.getString("Tools_WorkspaceHierarchy"));
    toolsMenu.add (i18n.getString("Tools_UIHierarchy"));
    toolsMenu.add (i18n.getString("Tools_RuntimeData"));
    toolsMenu.addSeparator();
    toolsMenu.add (i18n.getString("Tools_EnterPackagePreparationMode"));
    toolsMenu.add (i18n.getString("Tools_StripTextsNow"));
    toolsMenu.add (i18n.getString("Tools_MakeWorkspacesProprietaryNow"));
    toolsMenu.add (i18n.getString("Tools_FlushChangeLogForEntireKB"));
    toolsMenu.addSeparator();
    toolsMenu.add (i18n.getString("Tools_ReadFromFile"));
    toolsMenu.add (i18n.getString("Tools_WriteToFile"));
    toolsMenu.add (i18n.getString("Tools_Recompile"));
    toolsMenu.addSeparator();
    toolsMenu.add (i18n.getString("Tools_Customize"));
    return toolsMenu;
  }
  
  static MDIMenu createRunOptionsMenu () {
		
    MDIMenu runOptionsMenu = new MDIMenu (i18n.getString("G2_RunOptions"), false);

    runOptionsMenu.add (i18n.getString("G2_RunOptions_HighlightInvokedRules"));
    runOptionsMenu.add (i18n.getString("G2_RunOptions_EnableAllItems"));
    runOptionsMenu.add (i18n.getString("G2_RunOptions_RemoveTracingAndBreakPoints"));

    return runOptionsMenu;
  }

  static MDIMenu createG2Menu () {
    MDIMenu g2Menu = new MDIMenu (i18n.getString("G2"), false);

    g2Menu.add (startG2Item =
		new MDIMenuItem(i18n.getString("G2_StartResume")));
    g2Menu.add (pauseG2Item =
		new MDIMenuItem(i18n.getString("G2_Pause")));
    g2Menu.add (resetG2Item =
		new MDIMenuItem(i18n.getString("G2_Reset")));
    g2Menu.addSeparator();
    g2Menu.add (i18n.getString("G2_ChangeMode"));
    g2Menu.add (i18n.getString("G2_SimulateProprietaryMode"));
    g2Menu.addSeparator();
    g2Menu.add ((MDIMenu)RUNOPTIONSMENU.clone());
    g2Menu.add (i18n.getString("G2_NetworkInformation"));
    g2Menu.add (i18n.getString("G2_ConnectToForeignImage"));
    g2Menu.add (i18n.getString("G2_DisconnectFromForeignImage"));

    return g2Menu;
  }

  static MDIMenu createInsertMenu () {
    MDIMenu insertMenu = new MDIMenu (i18n.getString("Insert"), false);
    
    insertMenu.add (newControlItem = new MDIMenuItem (i18n.getString("Insert_Control")));
    return insertMenu;
  }
  
  static MDIMenu createWindowMenu () {
    MDIMenu windowMenu = new MDIMenu (i18n.getString("Window"), false);

    windowMenu.add (cascadeItem = (MDIMenuItem)CASCADE_MENUITEM.clone ());
    windowMenu.add (tileHorizItem = (MDIMenuItem)TILEHORIZ_MENUITEM.clone ());
    windowMenu.add (tileVertItem = (MDIMenuItem)TILEVERT_MENUITEM.clone ());
    windowMenu.add (i18n.getString("Window_ArrangeIcons"));
    windowMenu.add (i18n.getString("Window_CloseAll"));
    return windowMenu;
  }

  static MDIMenu createDemoMenu () {
    MDIMenu demoMenu = new MDIMenu(i18n.getString("Demo"), false);

    demoMenu.add (chartItem = new MDIMenuItem(i18n.getString("Demo_SimpleChart")));
    demoMenu.add (newChartItem = new MDIMenuItem(i18n.getString("Demo_ImprovedChart")));
    demoMenu.add (getBeansDialogItem = new MDIMenuItem(i18n.getString("Demo_BeansDialog")));
    demoMenu.add (getUilDialogItem = new MDIMenuItem(i18n.getString("Demo_GetDialog")));
    demoMenu.add (stubItem = new MDIMenuItem(i18n.getString("Demo_stubTest")));
    demoMenu.add (testItem = new MDIMenuItem(i18n.getString("Demo_test")));
    demoMenu.add (subscribeShowingItem
		  = new MDIMenuItem(i18n.getString("Demo_SubscribeShowing")));
    demoMenu.add (unsubscribeShowingItem
		  = new MDIMenuItem(i18n.getString("Demo_UnsubscribeShowing")));
    return demoMenu;
  }

  static MDIMenu createDebugMenu () {
    MDIMenu debugMenu = new MDIMenu(i18n.getString("Debug"), false);

    debugMenu.add (jgiDebugItem = new MDICheckboxMenuItem(i18n.getString("Debug_JGI")));
    debugMenu.add (traceOnItem =
		   new MDICheckboxMenuItem(i18n.getString("Debug_TraceOn")));
    ((MDICheckboxMenuItem)traceOnItem).setState(Trace.getTraceOn());
    debugMenu.add (traceExOnItem =
		   new MDICheckboxMenuItem(i18n.getString("Debug_TraceExOn")));
    ((MDICheckboxMenuItem)traceExOnItem).setState(Trace.getTraceOn());
    MDIMenu genMenu = new MDIMenu (i18n.getString ("Debug_generation"), false);
    genMenu.add (genOnItem = new MDICheckboxMenuItem (i18n.getString ("Debug_gen_on")));
    genMenu.add (genOffItem = new MDICheckboxMenuItem (i18n.getString ("Debug_gen_off")));
    genMenu.add (genAutoItem = new MDICheckboxMenuItem (i18n.getString ("Debug_gen_auto")));
    activeGenModeItem = (MDICheckboxMenuItem)genOnItem;
    debugMenu.add (genMenu);
    return debugMenu;
  }

  static MDIMenu createHelpMenu () {
    MDIMenu helpMenu = new MDIMenu(i18n.getString("Help"), false);
    
    helpMenu.add(i18n.getString("Help_AboutG2"));
    return helpMenu;
  }

	static void disableMenuBarItems(MenuBar mbar) {
		Menu mbMenu;
		int count = mbar.getMenuCount();
		for (int i=0; i<count; i++) {
			mbMenu = mbar.getMenu(i);
			disableMenu((MDIMenu)mbMenu);
		}
	}

	static void disableMenu(MDIMenu mdiMenu) {
		MenuItem tempItem;
		int count = mdiMenu.getItemCount();
		for (int i=0; i<count; i++) {
			tempItem = mdiMenu.getItem(i);
			if (!(tempItem instanceof Menu))
			  tempItem.setEnabled(false);
		}
	}

	static void enableSomeMenuItems() {
		quitItem.setEnabled(true);
		openXnItem.setEnabled(true);
		switchItem.setEnabled(true);
		newWkspItem.setEnabled(true);
		newPanelItem.setEnabled(true);
		getNamedWkspItem.setEnabled(true);
		chartItem.setEnabled(true);
		newChartItem.setEnabled(true);
		getBeansDialogItem.setEnabled(true);
		newControlItem.setEnabled(true);
		cutItem.setEnabled(true);
		copyItem.setEnabled(true);
		pasteItem.setEnabled(true);
		cloneItem.setEnabled(true);
		deleteItem.setEnabled(true);
		selectAllItems.setEnabled(true);
		getUilDialogItem.setEnabled(true);
		cascadeItem.setEnabled(true);
		tileHorizItem.setEnabled(true);
		editItem.setEnabled(true);
		tileVertItem.setEnabled(true);
		jgiDebugItem.setEnabled(true);
		traceOnItem.setEnabled(true);
		traceExOnItem.setEnabled(true);
		genOnItem.setEnabled (true);
		genOffItem.setEnabled (true);
		genAutoItem.setEnabled (true);
		stubItem.setEnabled(true);
		testItem.setEnabled (true);
		subscribeShowingItem.setEnabled(true);
		unsubscribeShowingItem.setEnabled(true);
		startG2Item.setEnabled(true);
		pauseG2Item.setEnabled(true);
		resetG2Item.setEnabled(true);
		return;
	}

  static MenuBar createStandardMenuBar () {
    MenuBar mbar = new MenuBar ();
    mbar.add ((MDIMenu)FILEMENU.clone());
    mbar.add ((MDIMenu)EDITMENU.clone());

    mbar.add ((MDIMenu)VIEWMENU.clone());
    mbar.add ((MDIMenu)FORMATMENU.clone());
    mbar.add ((MDIMenu)LAYOUTMENU.clone());
    mbar.add ((MDIMenu)TOOLSMENU.clone());
    mbar.add ((MDIMenu)G2MENU.clone());

    mbar.add ((MDIMenu)INSERTMENU.clone ());
    mbar.add (windowMenu = (MDIMenu)WINDOWMENU.clone ());
    mbar.add ((MDIMenu)DEMOMENU.clone ());
    mbar.add ((MDIMenu)DEBUGMENU.clone ());
    mbar.setHelpMenu ((MDIMenu)HELPMENU.clone());

    disableMenuBarItems(mbar);
    enableSomeMenuItems();

    return mbar;
  }

  NtwFrame (String title) {
    super (title);
    setSize (900, 700);
    setMenuBar (createStandardMenuBar (), windowMenu);
    // Allow applications to call inform without knowing the frame
    com.gensym.dlg.MessageDialog.registerFrame (this);
  }

  @Override
  public boolean handleEvent (Event evt) {
    if (evt.id == Event.WINDOW_DESTROY)
      System.exit(0);
    
    if(evt.target instanceof MDIMenuItem || evt.target instanceof MDICheckboxMenuItem)
      return handleMenuEvent (evt);

    return super.handleEvent (evt);
  }

  @Override
  public void dialogDismissed (StandardDialog d, int code) {
    InputDialog med = (InputDialog)d;
    if (med.wasCancelled ()) {
      System.out.println ("Dialog was cancelled.");
      return;
    }
    
    System.out.println ("Dialog was okayed.");
    String[] results = med.getResults ();
    for (int i=0; i<results.length; i++)
      System.out.println (" #" + i + " :  " + results[i]);

    String url = ((new String("")).equals(results[0]) || (results[0] == null) ?
		  null : results[0]);

    lastConnectedURL  = results[0];
    lastConnectedHost = results[1];
    lastConnectedPort = results[2];

    application.attemptConnection (url, results[1], results[2]);
  }

  
  public boolean handleMenuEvent (Event evt) {
    Object evtSrc = evt.target;

    if (evtSrc instanceof MDICheckboxMenuItem) {
      MDICheckboxMenuItem cbitem = ((MDICheckboxMenuItem)evtSrc).getOriginal ();
      boolean currentState = cbitem.getState ();
      if (cbitem == jgiDebugItem) {
	application.getCurrentContext().setInterfaceDebugOptions (currentState);
	System.out.println ("Setting debug state of JGInterface to " + currentState);
      } else if (cbitem == traceOnItem) {
	Trace.setTraceOn (currentState);
	System.out.println ("Setting Trace state to " + currentState);
      } else if (cbitem == traceExOnItem) {
	Trace.setExceptionTraceOn (currentState);
	System.out.println ("Setting Trace Exception to " + currentState);
      } else if (cbitem == genOnItem || cbitem == genOffItem || cbitem == genAutoItem) {
	int mode;
	if (cbitem == genOnItem)
	  mode = StubClassLoader.GENERATION_ON;
	else if (cbitem == genOffItem)
	  mode = StubClassLoader.GENERATION_OFF;
	else
	  mode = StubClassLoader.GENERATION_AUTO;
	System.out.println ("Setting Generation Mode to " + mode);
	cbitem.setState (false);
	((G2Gateway)application.getCurrentContext()).setGenerationMode (mode);
	activeGenModeItem.setState (false);
	cbitem.setState (true);
	activeGenModeItem = cbitem;
	System.out.println ("Generation Mode Set!");
      }
      return true;
    }

    MDIMenuItem item = ((MDIMenuItem)evtSrc).getOriginal ();
    String label = item.getLabel ();
    //    System.out.println ("  " + label + " selected.");
      
    if(item == quitItem)
      System.exit(0);
      


    if (item == chartItem) {
      System.out.println("Making a simple Chart\n");
     
      SimpleChart chart = new SimpleChart ();
      chart.setInterface (application.getCurrentContext ());
      try {
      chart.testShow();
      } catch (G2AccessException g2ae) {
	System.out.println("Couldn't show SimpleChart" + g2ae);
	g2ae.printStackTrace();
      }
	
      return true;
    }
      
    if (item == newChartItem) {
      System.out.println("Making a new Chart\n");

      SimpleChart chart = new ImprovedChart ();
      chart.setInterface ( application.getCurrentContext () );
      try {
	chart.testShow();
      } catch (G2AccessException g2ae) {
	System.out.println("Couldn't show ImprovedChart" + g2ae);
	g2ae.printStackTrace();
      }
	
      return true;
    }

    if (item == getBeansDialogItem)
      {
	try {
	  G2Access context = application.getCurrentContext ();
	  Symbol name = Symbol.intern("THING-1");
	  Symbol className = Symbol.intern("THING");
	  Object result = context.getUniqueNamedItem(className,name);
	  //G2ItemProxy proxy = (G2ItemProxy) result;
	  /* BeanPanel.runTestDialog(this,proxy); */
	} catch (G2AccessException g2ae) {
	}
	catch (Exception ex) {
	  System.out.println("Could not run test dialog -- no proxy found");
	}
      }

    if (item == openXnItem) {
      System.out.println ("Opening Connection Dialog...");
      System.out.flush ();
      String[] labels = {"Url:", "Host:", "Port:"};

      String[] initialValues = {lastConnectedURL, lastConnectedHost, lastConnectedPort};
	
      new InputDialog (this, "Initiate Connection", false,
			   labels, new String[] {"Connect", "Cancel"},
			   (StandardDialogClient) this).setVisible (true);
      System.out.println ("Finished Building dialog");
      System.out.flush ();
      return true;
    }
      
    if (item == stubItem) {
      System.out.println ("Running Stub Test...");
      System.out.flush ();
      G2Access context = application.getCurrentContext ();
      try {
	Object x = context.getUniqueNamedItem (Symbol.intern ("KB-WORKSPACE"),
					       Symbol.intern ("NIRVANA"));
	System.out.println ("Got KB-WORKSPACE named NIRVANA -> " + x);
	KbWorkspace wksp = (KbWorkspace) x;
	System.out.println ("Downloaded Workspace Stub! Setting up dialog");
	String[] labels = {"Margin", "Background Color", "ForeGroundColor", "X Position"};
	int margin = wksp.getWorkspaceMargin ();
	Symbol bgColor = wksp.getBackgroundColor ();
	Symbol fgColor = wksp.getForegroundColor ();
	System.out.println (" ??? Got fgColor = " + fgColor + " ---> Going for initWidth");
	//int edgeDelta = wksp.getEdgeDelta ();
	//Structure c = wksp.getContents ();
	//System.out.println ("EdgeDelta = " + edgeDelta + "\nContents = " + c);
	System.out.flush ();
	int initWidth = wksp.getItemXPosition ();
	boolean instantiate = wksp.getInstantiateForClass ();
	String[] initialValues = {Integer.toString (margin), bgColor.getPrintValue (), fgColor.getPrintValue (), //Integer.toString (initWidth)};
				  new Boolean (instantiate).toString ()};
	WkspDialogHandler wkspDlgHandler = new WkspDialogHandler (wksp);
	new InputDialog (this, "ZZTOP Properties", false, labels,
			     new String[] {"Commit", "Cancel"}, (StandardDialogClient)wkspDlgHandler).setVisible (true);
	System.out.println ("Finished Building dialog");
	System.out.flush ();
      } catch (Exception e) {
	e.fillInStackTrace ();
	System.err.println (e);
	new MessageDialog (NtwFrame.this,
			  "Error during Workspace Retreival",
			  false,
			  e.toString (),
			  (StandardDialogClient)null).setVisible (true);
      }
      return true;
    }


    if (item == testItem) {
      System.out.println ("Running embedded items test!");
      TwAccess context = (TwAccess)application.getCurrentContext ();
      Object x = null;
      return true;
    }

    if (item == subscribeShowingItem)
      {
	System.out.println("attempting subscribe showing");
	TwAccess context = (TwAccess)application.getCurrentContext ();
	try {
	context.addWorkspaceShowingListener(this);
	} catch (G2AccessException gae) {System.err.println (gae);}
      }
    if (item == unsubscribeShowingItem)
      {
	System.out.println("attempting unsubscribe showing");
	TwAccess context = (TwAccess)application.getCurrentContext ();
	try {
	  context.removeWorkspaceShowingListener(this);
	} catch (G2AccessException gae) {System.err.println (gae);}
      }

    if (item == newWkspItem) {
      TwAccess context = (TwAccess)application.getCurrentContext ();
      Symbol KB_WORKSPACE_ = Symbol.intern("KB-WORKSPACE");
      KbWorkspace kbWorkspace = null;
      Symbol newWorkspaceName
	= Symbol.intern("NEW-WS-" + WorkspaceUtil.newWorkspaceCount++);
      try {
 	kbWorkspace = (KbWorkspace)context.createItem(KB_WORKSPACE_);
	//Symbol PROCEDURE_ = Symbol.intern("PROCEDURE");
 	//context.resizeItem(kbWorkspace,0, 100, 150, 0, Symbol.intern("FOO-MODE"));
 	//((com.gensym.classes.Block)kbWorkspace).setNames(newWorkspaceName);
 	//Item procedure = context.createItem(PROCEDURE_);
 	//context.transferItem(procedure, kbWorkspace, 75, 75);
 	//context.resizeItem(procedure, 50, 50, 125, 0, Symbol.intern("FOO-MODE"));
 	//Item procedureClone = context.cloneItem(procedure);
 	//context.transferItem(procedureClone, kbWorkspace, 125, 125);
      } catch (G2AccessException gae) {System.err.println (gae);}
      WorkspaceView view = new WorkspaceView (kbWorkspace);
      Rectangle initialBounds = view.getBounds();
      int initialLeft = initialBounds.x;
      int initialTop = initialBounds.y;
      int initialWidth = initialBounds.width;
      int initialHeight = initialBounds.height;
      view.setEventHandler (new RubberBandHandler ());
      int scrollBarWidth = 15;
      MDIDoc newpanel
 	= createNewDocument (newWorkspaceName.toString(),
 			     new Dimension (initialWidth + scrollBarWidth,
 					    initialHeight + scrollBarWidth));
      newpanel.setLayout (new BorderLayout ());
      ViewScrollbar hscroll = new ViewScrollbar (view,Scrollbar.HORIZONTAL, 0,1,
 						 initialLeft, initialLeft + initialWidth);
      ViewScrollbar vscroll = new ViewScrollbar (view,Scrollbar.VERTICAL, 0,1,
 						 initialTop, initialTop + initialHeight);
      view.addScrollbar(vscroll,false);
      view.addScrollbar(hscroll,true);
      newpanel.add("South",  hscroll);
      newpanel.add("East",   vscroll);
      newpanel.add("Center", view);
      newpanel.validate();
      newpanel.setVisible(true);
      view.setDoubleBuffered (true);      
      new NtwNotification (NtwNotification.STATUSCHANGE,
 			   0, "", this, NtwNotification.ACTIVITY_STOP).send ();
      newpanel.registerUserObject (view);
      return true;
    }
    
    if (item == newPanelItem) {
      MDIDoc newPanel = createNewDocument ("CLIENT-SIDE-PANEL");
      newPanel.setLayout (new BorderLayout ());
      WorkspaceView w = new WorkspaceView ();
      w.setDoubleBuffered (false);
      System.out.println ("Before Set!"); System.out.flush ();
      w.setEventHandler (new com.gensym.wksp.RubberBandHandler ());
      System.out.println ("After Set!"); System.out.flush ();
      w.setBackgroundColor (Color.white);
      Dimension sz = newPanel.getSize ();
      w.setOutOfBoundsColor (Color.cyan);
      newPanel.add ("Center", w);
      newPanel.validate ();
      w.setScroll (0, 0, sz.width, sz.height);
      System.out.println ("BNS: Added new workspace with scroll init: " +
			  0 + " " + 0 + " " + sz.width + " " + sz.height);
      System.out.println ("Logical Bounds = " + w.getLogicalBounds ());
      System.out.println ("View Bounds    = " + w.getViewBounds ());
      newPanel.list ();
      newPanel.registerUserObject (w);
      return true;
    }
    
    if (item == getNamedWkspItem) {
      new Thread (new GetWkspHandler (application.getCurrentContext ())).start ();
      return true;
    }

    if (item == startG2Item) {
      try {
	((TwGateway)application.getCurrentContext()).setG2State(TwGateway.RUNNING_);
      } catch (G2AccessException g2ae) {}
      return true;
    }

    if (item == pauseG2Item) {
      try {
	((TwGateway)application.getCurrentContext()).setG2State(TwGateway.PAUSED_);
      } catch (G2AccessException g2ae) {}
      return true;
    }

    if (item == resetG2Item) {
      try {
	((TwGateway)application.getCurrentContext()).setG2State(TwGateway.RESET_);
    } catch (G2AccessException g2ae) {}
      return true;
    }
    if (item == editItem) {
      MDIDoc currentDoc = getFocusDocument ();
      if (currentDoc == null)
	return true;
      WorkspaceView wksp = (WorkspaceView) currentDoc.getUserObject ();
      if (wksp == null)
	return true;
      WorkspaceElement[] seln      = wksp.getSelection ();
      System.out.println ("There are " + seln.length + " elements in the selection");
      if (seln.length != 1)
	return true;
      WorkspaceElement firstSeln = seln[0];
      try {
	//firstSeln.editItem ();
      } catch (Exception g2ae) {
	//fix this: need notification sent.
	g2ae.printStackTrace();
      }
      return true;
    }
    
    if (item == getNamedWkspItem) {
      new Thread (new GetWkspHandler (application.getCurrentContext ())).start ();
      return true;
    }

    if (item == getUilDialogItem) {
      //new Thread (new getUilDialogHandler (application.getCurrentContext ())).start ();
      return true;
    }
    
    return super.handleEvent (evt);
    //      return getFocusDocument().handleMenuEvent (evt);
  }
  
  class WkspDialogHandler implements StandardDialogClient {
    private KbWorkspace wksp;

    WkspDialogHandler (KbWorkspace wksp) {
      this.wksp = wksp;
    }

    @Override
    public void dialogDismissed (StandardDialog d, int code) {
      InputDialog med = (InputDialog)d;
      if (med.wasCancelled ()) {
	System.out.println ("Dialog was cancelled.");
	return;
      }
      
      System.out.println ("Dialog was okayed.");
      String[] results = med.getResults ();
      for (int i=0; i<results.length; i++)
	System.out.println (" #" + i + " :  " + results[i]);
      
      try {
	int margin = Integer.parseInt (results[0]);
	Symbol bgColor = Symbol.intern (results[1]);
	Symbol fgColor = Symbol.intern (results[2]);
	wksp.setWorkspaceMargin (margin);
	wksp.setForegroundColor (fgColor);
	wksp.setBackgroundColor (bgColor);
      } catch (Exception e) {
	System.err.println (e);
	new MessageDialog (NtwFrame.this,
			  "Error during Workspace Commit",
			  false,
			  e.toString (),
			  (StandardDialogClient) null).setVisible (true);
      }
    }
  }

  @Override
  public void showWorkspace(WorkspaceShowingEvent event)
  {
    System.out.println("G2 request to show "+ event);
  }

  @Override
  public void hideWorkspace(WorkspaceShowingEvent event)
  {
    System.out.println("G2 requests to hide "+ event);
  }
}
