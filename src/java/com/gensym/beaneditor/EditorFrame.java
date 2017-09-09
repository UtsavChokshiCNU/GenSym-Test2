package com.gensym.beaneditor;


import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Locale;
import java.util.Observer;
import java.util.Observable;

import com.gensym.draw.PersistentCanvas;
import com.gensym.draw.ViewScrollbar;
import com.gensym.draw.ViewScrollState;
import com.gensym.draw.RectElement; // for testing only

import com.gensym.message.Resource;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.Trace;
import com.gensym.files.URLFile;

import com.gensym.ui.Command;
import com.gensym.ui.menu.awt.CMenu;
import com.gensym.ui.menu.awt.CMenuBar;
import com.gensym.ui.menu.awt.CPopupMenu;
import com.gensym.ui.toolbar.ToolBar;

import java.io.PrintStream;

public class EditorFrame extends Frame
{
  //Our honorable parent-pointer
  ComponentEditor application;

  // Layout and Contents
  private BeanCanvas canvas = null;
  private BeanMessageOut error;
  private BeanEditTool beanEditTool;
  private BeanDebugTool beanDebugTool;
  private int appHeight = 600;
  private int appWidth = 800;
  private Panel clientPanel;
  ViewScrollbar vScroll;
  ViewScrollbar hScroll;
  static final int SIMPLE_DIALOG = 1;
  static final int TABBED_DIALOG = 2;
  private int dialogType = SIMPLE_DIALOG;

  private BeanStatusBar statusBar;
  private ToolBar toolBar;
  private BeanToolBarPanel toolBarPanel;
  private String title = "";

  // Menus and Menu Items
  private CMenuBar menuBar;
  private CMenu pageMenu = new CMenu("Page");
  private CMenu helpMenu = new CMenu("Help");

  // UI Commands
  private FileCommands fileCommands;
  private EditCommands editCommands;
  private ViewCommands viewCommands;
  private EventConnectionCommands eventCxnCommands;
  private FriendConnectionCommands friendCxnCommands;
  private InsertEventConnectionCommand insertEventCommands, popupInsertEventCommand;
  private InsertFriendConnectionCommand insertFriendCommand, popupInsertFriendCommand;
  private LayoutCommands layoutCommands;
  private ModeCommands modeCommands;
  private ToolsCommands toolsCommands;
  private BeanifierCommands beanifierCommands;
  private PageCommands pageCommands;
  private PageGroupCommands pageGroupCommands;
  private PaletteCommands paletteCommands;
  private Command helpCommands;

  private CPopupMenu popup;
  
  private boolean debugMode = false;
  // 2-do
  // build/play modes
  //   - new BeanDebugTool (as opposed to edit tool)
  //      default behavior, like flashing in debug mode (maybe a real CBoxMenuITem)
  //   - itemProxy testing harness, i.e. setting up the fetching of items from G2
  //     into named items for testlauncher to do the right thing.
  //      (maybe make these settings sticky)
  //   - per-component layout constraints (+ default ordering)
  // re-do standard hookup for thread issues
  //    - 0 find out w-t-hell thread is running before suspend
  //    - 1 start thread to info clients of pause
  //    - 2 suspend self

  //    - 3 await resumption
  // pageMenu - tab editingMode
  //   - kill multiple open and new menu choices
  //   - make new simple/tabbed sub menu choices
  // preference object
  //   HookupEditor - simple/G2Script/Java/Choose
  //   DefaultJars - ListOfFileNames
  // preference dialog
  // canvas sizing re-work/out-of-bounds areas
  //   - painting bugs (synchronized BCanvas paint??)
  //   - mouse handling bugs - gestures can go to hell
  //                         - new event port can get confused and fail
  //   - canvas sizing doo-hickeys (posts and lines)
  //   - linking canvas (Component.getBounds()) growth through re-sizing to 
  //     to logical size
  //   - provide a shrink-wrap option for trimming excess logical size
  //   - opening saved (large) dialogs vs. canvas initial state
  // multiple selection
  // cut/paste
  // save modes

  // VKP q's
  // closer bean (must always fire, etc)
  // inform dialog location
  // little upper-left icon could be gensym logo, not java cup
  // do we have an image button

  // Standard Tracing/Messages Stuff
  private static Resource i18n = 
  Resource.getBundle("com.gensym.resources.Messages", Locale.getDefault());
  private static int GUI_LEVEL = 2;
  private static boolean javaWillCrashWithPopupMenuTitle = true;
  static {
    try {
      javaWillCrashWithPopupMenuTitle = (System.getProperty ("os.name").toLowerCase().indexOf ("windows") >= 0);
    } catch (Exception e) {
      // Who cares?
    }
  }

  
  private void sendErrorMessage(String key, Object args[])
  {
    Message.send(new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor", EditorFrame.class, i18n, key, (args == null) ? new Object[]{} : args));
  }

  EditorFrame(String title, ComponentEditor application)
  {
    super(title);
    this.application = application;
    this.title = title;
    toolBarPanel = new BeanToolBarPanel();
    toolBar = new ToolBar();
    toolBarPanel.add(toolBar);
    statusBar = new BeanStatusBar();
    pageCommands = new PageCommands(this, pageMenu);
    pageGroupCommands = new PageGroupCommands(this, pageCommands);
    fileCommands = new FileCommands(this, pageCommands, pageGroupCommands);
    editCommands = new EditCommands(this);
    viewCommands = new ViewCommands(this);
    layoutCommands = new LayoutCommands(this);
    if (application.beanifier != null)
      beanifierCommands = new BeanifierCommands(this);
    modeCommands = new ModeCommands(this, pageGroupCommands, viewCommands);
    toolsCommands = new ToolsCommands(this);
    paletteCommands = new PaletteCommands(application);
    eventCxnCommands = new EventConnectionCommands(this);
    friendCxnCommands = new FriendConnectionCommands(this);
    insertEventCommands = new InsertEventConnectionCommand(this, "Event", true);
    popupInsertEventCommand = new InsertEventConnectionCommand(this, "New Event", false);
    insertFriendCommand = new InsertFriendConnectionCommand(this, "Access Link");
    popupInsertFriendCommand = new InsertFriendConnectionCommand(this, "New Access Link");
    helpCommands = new HelpCommands(this);
  }
  
  void startup()
  {
    error = new BeanMessageOut(this);

    addWindowListener
      (
       new WindowAdapter ()
       {
	 @Override
	 public void windowClosing(WindowEvent e)
	   {
	     //EditorFrame frame = (EditorFrame) e.getWindow();
	     //frame.setVisible(false);
	     //frame.dispose();
	     //frame.application.removeFrame(frame);
	     fileCommands.actionPerformed(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, fileCommands.EXIT));
	   }
       } ) ;

    //Build Menu via Commands
    menuBar = new CMenuBar();
    
    CMenu fileMenu = new CMenu("File");
    fileMenu.add(fileCommands);
    menuBar.add(fileMenu);

    CMenu editMenu = new CMenu("Edit");
    //editMenu.add(editCommands, editCommands.CUT);
    //editMenu.add(editCommands, editCommands.COPY);
    //editMenu.add(editCommands, editCommands.PASTE);
    //editMenu.addSeparator();
    editMenu.add(editCommands, editCommands.DELETE);
    //editMenu.add(pageCommands, pageCommands.DELETE_PAGE);
    editMenu.add(editCommands, editCommands.SELECT_ALL);
    editMenu.addSeparator();
    editMenu.add(editCommands, editCommands.EDIT);
    editMenu.add(editCommands, editCommands.PROPERTIES);
    //editMenu.add(pageCommands, pageCommands.PAGE_PROPERTIES);
    menuBar.add(editMenu);

    CMenu viewMenu = new CMenu("View");
    menuBar.add(viewMenu);
    viewMenu.add(paletteCommands);
    viewMenu.addSeparator();
    viewMenu.add(viewCommands);
    
    CMenu layoutMenu = new CMenu("Layout");
    menuBar.add(layoutMenu);
    layoutMenu.add(layoutCommands);

    CMenu insertMenu = new CMenu("Insert");
    menuBar.add(insertMenu);
    //insertMenu.add(pageCommands, pageCommands.NEW_PAGE);
    //insertMenu.addSeparator();
    insertMenu.add(insertEventCommands);
    insertMenu.add(insertFriendCommand);
    
    CMenu toolsMenu = new CMenu("Tools");
    menuBar.add(toolsMenu);
    
    toolsMenu.add(modeCommands);
    if (application.beanifier != null) {
      insertMenu.addSeparator();
      insertMenu.add(beanifierCommands, ((BeanifierCommands)beanifierCommands).OLE_OBJECT);
      toolsMenu.addSeparator();
      toolsMenu.add(toolsCommands, toolsCommands.BEAN_BUILDER);
      toolsMenu.add(beanifierCommands, ((BeanifierCommands)beanifierCommands).CONVERT_ACTIVEX_CONTROL);
      toolsMenu.addSeparator();
      toolsMenu.add(toolsCommands, toolsCommands.PREFERENCES);
    }
    else toolsMenu.add(toolsCommands);
    
    menuBar.add(helpMenu);
    helpMenu.add(helpCommands);

    setMenuBar(menuBar);

    //popup menu
    popup = new CPopupMenu();

    //toolbar
    toolBar.add(fileCommands, fileCommands.DIALOG);
    //toolBar.add(fileCommands, fileCommands.TABBED_DIALOG);
    toolBar.addSeparator();
    toolBar.add(fileCommands, fileCommands.OPEN);
    toolBar.add(fileCommands, fileCommands.SAVE);
    //toolBar.addSeparator();
    //toolBar.add(editCommands, editCommands.CUT);
    //toolBar.add(editCommands, editCommands.COPY);
    //toolBar.add(editCommands, editCommands.PASTE);
    toolBar.addSeparator();
    toolBar.add(modeCommands,modeCommands.RUN_BUILD_MODE);

    //setBackground (Color.gray);
    setSize(appWidth,appHeight);
    clientPanel = new Panel() {
      @Override
      public void update (Graphics g) {
    	  paint (g);
      }
    };
    add("Center", clientPanel);
    add("North", toolBarPanel);
    add("South", statusBar);
    // Frame (tool/client/status) (as N C S in border layout)
    // clinet (canvas / hbar / vbar) (as C S E in border layout)

    BeanCanvas newCanvas = new BeanCanvas();
    newCanvas.setBackgroundColor(Color.white);
    //canvas.setBackground(Color.white);
    Preferences prefs = Preferences.currentPreferences;
    newCanvas.setContainerSize(prefs.getDefaultContainerWidth(), 
			       prefs.getDefaultContainerHeight());

    vScroll = new ViewScrollbar(newCanvas, 1, 50, 50, 0, 100);
    hScroll = new ViewScrollbar(newCanvas, 0, 50, 50, 0, 100);

    clientPanel.setLayout(new BorderLayout());
    clientPanel.add("South", hScroll);
    clientPanel.add("East", vScroll);
    clientPanel.add("Center", newCanvas);
    
    setVisible(true);
    setCanvas(newCanvas);
  }

  void setCanvas(BeanCanvas newCanvas)
  {
    if (canvas != null)
      clientPanel.remove(canvas);
      
    canvas = newCanvas;
    clientPanel.add("Center", canvas);

    BeanEditTool oldBeanEditTool = beanEditTool;
    beanEditTool = new BeanEditTool(canvas, this);
    if (oldBeanEditTool != null){
      beanEditTool.dirtyBit = oldBeanEditTool.dirtyBit;
    }
    beanDebugTool = new BeanDebugTool(canvas, this);
    
    if (application.inDesignMode())
      canvas.setEventHandler(beanEditTool);
    else
      canvas.setEventHandler(beanDebugTool);

    canvas.add(popup);

    hScroll.setScrollable(canvas);
    vScroll.setScrollable(canvas);
    canvas.getScrollState(false).addObserver(vScroll);
    canvas.getScrollState(true).addObserver(hScroll);
    ScrollAdapter scrollAdapter = new ScrollAdapter(canvas);
    canvas.getScrollState(false).addObserver(scrollAdapter);
    canvas.getScrollState(true).addObserver(scrollAdapter);

    canvasBoundsReport("before setScroll");
    canvas.setScroll();
    canvasBoundsReport("after setScroll");
    if (application.doubleBuffer)
      canvas.setDoubleBuffered(true);
    validate();
  }

  synchronized void launchComplete()
  {
    modeCommands.launchComplete();
  }

  synchronized boolean isRunningTestDialog()
  {
    return modeCommands.isRunningTestDialog();
  }

  void openResource (URLFile location) {
    fileCommands.doOpen (location);
  }

  boolean isDebugMode(){
    return debugMode;
  }

  @Override
  public void update (Graphics g) {
    paint (g);
  }

  void setDebugMode(boolean debug){
    debugMode = debug;
    modeCommands.updateAvailability();
  }

  boolean isDebugWindowVisible(){
    return modeCommands.isDebugWindowVisible();
  }

  void  setDebugWindowVisible(boolean visible){
    modeCommands.setDebugWindowVisible(visible);
  }

  private String getBeanShortName(String name){
    return name.substring(name.lastIndexOf(".") + 1);
  }

  void setBeanSelection(String newBeanSelection)
  {
    canvas.setNewBeanClass(newBeanSelection);
    if (newBeanSelection != null)
      statusBar.setStatus("Click and drag to add "+getBeanShortName(newBeanSelection));
    else
      statusBar.resetStatus();
  }

  void updateEditMenu()//changes in selection from BeanEditTool
  {
    editCommands.updateAvailability();
    layoutCommands.updateAvailability();
    insertEventCommands.updateCurrentWrapper();
    insertFriendCommand.updateAvailability();
  }

  void makePalette(G2JarInfo g2JarInfo)
  {
    paletteCommands.addPalette(g2JarInfo);
  }

  void updateViewMenuForAdd(Port port){
    viewCommands.addEvent(port);
  }

  void updateViewMenuForDelete(Port port){
    viewCommands.removeEvent(port);
  }

  void updateToolsMenu()//changes in mode (ready vs. run)
  {
    modeCommands.updateAvailability();
    if (beanifierCommands != null) beanifierCommands.updateAvailability();
  }

    
  void canvasBoundsReport(String message)
  {
    if (canvas != null && false)
      {
	System.out.println("canvas bounds at "+message);
	Rectangle bounds = canvas.getBounds();
	System.out.println("simple  bounds ="+((bounds == null) ? "<no bounds>" :
					       bounds.toString()));
	bounds = canvas.getLogicalBounds();
	System.out.println("logical bounds ="+(bounds == null ? "<no bounds>" : 
					       bounds.toString()));
	bounds = canvas.getViewBounds();
	System.out.println("view    bounds ="+(bounds == null ? "<no bounds>" : 
					       bounds.toString()));
      }
  }
  
  boolean containsNonTrivialComponents()
  {
    if (dialogType == SIMPLE_DIALOG)
      return canvas.containsNonTrivialComponents();
    for (PageNode pageNode = pageCommands.getFirstPage(); pageNode != null; pageNode = pageNode.next)
      if (pageNode.canvas.containsNonTrivialComponents())
	return true;
    return false;
  }

  // Clear Editing session should leave thins almost
  // ready for editing a new, simple dialog
  void clearEditingSession()
  {
    beanEditTool.clearSelection();
    //canvas.setNewBeanClass(null);
    clearCanvas(canvas);
    
    Preferences prefs = Preferences.currentPreferences;
    canvas.setContainerSize(prefs.getDefaultContainerWidth(), 
			    prefs.getDefaultContainerHeight());
    canvas.repaintIt();
    HookupFactory.clearHookups(); // this is too general
    viewCommands.reset();
  }

  private void clearCanvas(BeanCanvas canvas)
  {
    Component elements[] = canvas.getComponents();
    for (int i = 0; i < elements.length; i++)
      canvas.remove(elements[i]);
    canvas.containsBadBeans = false;
  }

  private void updatePageMenu()
  {
    if (dialogType == SIMPLE_DIALOG)
      {
	menuBar.remove(helpMenu);
	menuBar.remove(pageMenu);
	menuBar.add(helpMenu);
      }
    else
      {
	menuBar.remove(helpMenu);
	menuBar.add(pageMenu);
	menuBar.add(helpMenu);
      }
    pageCommands.updateAvailability();
  }

  void dropOccurred(){
    paletteCommands.dropOccurred();
  }

  void setupSimpleDialog()
  {
    dialogType = SIMPLE_DIALOG;
    pageCommands.reset();
    updatePageMenu();
  }

  void setupTabbedDialog(boolean makeFirstPages)
  {
    dialogType = TABBED_DIALOG;
    pageCommands.reset();
    if (makeFirstPages)
      pageCommands.makeFirstPages();
    updatePageMenu();
  }

  int getDialogType(){
    return dialogType;
  }

  BeanCanvas getCanvas(){
    return canvas;
  }

  BeanEditTool getBeanEditTool(){
    return beanEditTool;
  }

  BeanDebugTool getBeanDebugTool(){
    return beanDebugTool;
  }

  BeanStatusBar getStatusBar(){
    return statusBar;
  }

  BeanToolBarPanel getToolBarPanel(){
    return toolBarPanel;
  }

  void updateTitle(String fileName){
    setTitle(title+" - "+fileName);
  }

  PopupMenu getPopupMenu(Component element, int x, int y){
    popup.removeAll();
    if (element instanceof Wrapper){
      if (((Wrapper)element).bean != null){
	String className = ((Wrapper)element).bean.getClass().getName();
	if (!javaWillCrashWithPopupMenuTitle)
	  popup.setLabel (className.substring (className.lastIndexOf ('.') + 1, className.length()));
	Wrapper w = (Wrapper)element;
	popupInsertEventCommand.updateCurrentWrapper(w);
	popupInsertEventCommand.setPosition(x, y);
	popup.add(popupInsertEventCommand);
	popupInsertFriendCommand.updateAvailability();
	popup.add(popupInsertFriendCommand);
	popup.addSeparator();
	popup.add(editCommands, editCommands.DELETE);
	popup.addSeparator();
	popup.add(editCommands, editCommands.EDIT);
	popup.add(editCommands, editCommands.PROPERTIES);
      }
    }
    else if (element instanceof EventConnection || element instanceof LooseEnd || element instanceof Port){
      if (!javaWillCrashWithPopupMenuTitle)
	popup.setLabel ("Event");
      eventCxnCommands.setPopupElement(element);
      popup.add(eventCxnCommands);
    }
    else if (element instanceof KnowledgeLink || element instanceof KnowledgeLinkLooseEnd){
      if (!javaWillCrashWithPopupMenuTitle)
	popup.setLabel ("Access Link");
      friendCxnCommands.setPopupElement(element);
	popup.add(friendCxnCommands);
    }
    return popup;
  }

  void updateConnectionColors(BeanCanvas canvas){
    ColorMap map = Preferences.currentPreferences.getEventColorMapping();
    Component[] elements = canvas.getComponents();
    for (int i = 0; i < elements.length; i++){
      if (elements[i] instanceof Port){
	Port port = (Port)elements[i];
	if (!port.getIsInput()){
	  EventInfo eventInfo = port.getEventInfo();
	  Color color = (Color)map.get(eventInfo.name);
	  if (color != null){
	    eventInfo.color = color;
	    port.getConnection().changeColor("inside", eventInfo.color);
	  }
	  else {
	    map.put(eventInfo.name, port.getConnection().getColor("inside"));
	  }
	}
      }
    }
  }
  
  void updateConnectionColors(){
    if (dialogType == SIMPLE_DIALOG)
       updateConnectionColors(canvas);
    else{
      for (PageNode pageNode = pageCommands.getFirstPage(); pageNode != null; pageNode = pageNode.next)
	updateConnectionColors(pageNode.canvas);   
    }
  }
 
  MySecurityManager ms = new MySecurityManager();

  class MySecurityManager extends SecurityManager {
    Class[] getClassesOnStack () {
      return getClassContext ();
    }
  };
  private static final Rectangle SMALL_RECTANGLE = new Rectangle (0, 0, 1, 1);
  @Override
  public Rectangle getBounds () {
    Class[] classes = ms.getClassesOnStack ();
    if (classes[2].getName ().equals ("javax.swing.ToolTipManager"))
      return SMALL_RECTANGLE;
    else
      return super.getBounds ();
  }

} // end of EditorFrame class definition

class ScrollAdapter implements Observer
{
  private BeanCanvas canvas;
  private int lastX;
  private int lastY;

  ScrollAdapter(BeanCanvas canvas)
  {
    this.canvas = canvas;
    lastX = canvas.getScrollState(true).getViewMin();
    lastY = canvas.getScrollState(false).getViewMin();
  }

  @Override
  public void update(Observable observable, Object arg)
  {
    ViewScrollState state = (ViewScrollState) observable;
    if (state.isHorizontal())
      {
	int minX = state.getViewMin();
	canvas.updateForScroll(lastX - minX,0);
	lastX = minX;
      }
    else
      {
	int minY = state.getViewMin();
	canvas.updateForScroll(0,lastY - minY);
	lastY = minY;
      }
  }

}

