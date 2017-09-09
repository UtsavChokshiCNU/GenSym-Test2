/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2TextEditor.java
 *
 */
package com.gensym.editor.text;

import java.awt.Image;
import java.awt.Toolkit;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Frame;
import java.awt.Dialog;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.List;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextArea;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.awt.Rectangle;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextField;
import javax.swing.BoxLayout;
import javax.swing.BorderFactory;
import javax.swing.border.EmptyBorder;
import javax.swing.text.JTextComponent;
import com.gensym.core.GensymLogo;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ui.Command;
import com.gensym.ui.menu.CMenu; //
import com.gensym.ui.menu.CMenuBar; //
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.toolbar.ToolBar;
import javax.swing.SwingConstants;



public class G2TextEditor extends JFrame  { 

  private static final boolean debug = false;


  //---- i18n -------
  private static Resource commands = 
  Resource.getBundle("com/gensym/editor/text/CommandShortResource");

  private static Resource i18n = 
  Resource.getBundle("com/gensym/editor/text/TextEditorLabels");



  //------- Accessors --------

  private ToolBar toolBar;
  public ToolBar getToolBar() { return toolBar; }

  private JPanel toolBarAndOther;

  private G2Editor editor;
  public G2Editor getEditor() { return editor; }
  public void setEditor(G2Editor e) { editor = e; }

  private JLabel statusLabel;
  public JLabel getStatusLabel() { return statusLabel; }
  public void setStatusLabel(JLabel l) { statusLabel = l; }


  private JPanel promptsPanel;

  private JPanel completionPanel;
  private JPanel categoryPanel;
  private JPanel itemsPanel;
  public JPanel getCompletionPanel() { return completionPanel; }
  public JPanel getCategoryPanel() { return categoryPanel; }
  public JPanel getItemsPanel() { return itemsPanel; }

  private JLabel statusText;
  public JLabel getStatusText() { return statusText; }
  public void setStatusText(JLabel t) { statusText = t; }

  private JLabel errorText;
  public JLabel getErrorText() { return errorText; }
  public void setErrorText(JLabel err) { errorText = err; }

  private JPanel statusBar;
  public JPanel getStatusBar() { return statusBar; }

  private JPanel statusAndUnicoder;

  private JPanel promptPanel;
  private GridBagLayout promptLayout;
  private GridBagConstraints pc;
  JSplitPane splitter;

  private Session session;
  void setSession(Session s) { session = s; }

  private PromptManager promptManager;
  private StatusManager statusManager; 

  public StatusManager getStatusManager(){ return statusManager; }

  public PromptManager getPromptManager(){ return promptManager; }


  private SessionCommands sessionHandler = null;
  SessionCommands getSessionHandler() { return sessionHandler; }

  private EditCommands editHandler = null;
  EditCommands getEditHandler() { return editHandler; }

  private ExportCommands export = null;
  ExportCommands getExport() { return export; }

  private ViewCommands view = null;
  ViewCommands getViewCommands() { return view; }

  

  private int promptsWidth = 150;
  private int promptsHeight = 300;

  private double percentageToText = .7;
  public double getSplitterRatio() { return percentageToText; }
  public void setSplitterRatio(double r) { percentageToText = r; }

  private ResizeListener resizer;
  private myWindowAdapter closingAdapter;

  JScrollPane textscroller;

  private boolean populated = false;
  boolean getPopulated() { return populated; }

  //--------- Constructors -----------

  public G2TextEditor() {
    super();
  }

  public G2TextEditor(Session session) {
    populateG2TextEditor(session);
  }

  void populateG2TextEditor(Session session) {  

    this.session = session;
    this.editor = session.getEditor();
    
    setBackground(Color.lightGray);


    setIconImage( GensymLogo.get() );



    //------ The Toolbar ---------
    toolBar = createToolBar();

    //------ Provision for including the Font Chooser or GoTo ---
    toolBarAndOther = new JPanel();
    toolBarAndOther.setLayout( new BorderLayout() );

    toolBarAndOther.add(toolBar, BorderLayout.WEST);
    /* The FontChooser/GoTo will go into the EAST sector. */


    // ------ the type-in Area (TextView class) ------

    editor = session.getEditor();
    textscroller = 
      new JScrollPane((java.awt.Component)editor, 
		      JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED,
		      JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);


    //-------- prompts

    promptsPanel = new JPanel();
    promptsPanel.setLayout( new GridLayout(0, 3, // three columns
				      2, 0  // two pixels apart
				      ));
   
    completionPanel = makePromptPanel("LanguagePrompts",
				      session.getPromptView() );
    categoryPanel = makePromptPanel("ItemTypes",
				    session.getCategoryView() );
    itemsPanel = makePromptPanel("ItemNames",
				 session.getCategoryTokensView() );

    // size the prompts
    completionPanel.setPreferredSize( new Dimension(promptsWidth, promptsHeight));
    categoryPanel.setPreferredSize( new Dimension(promptsWidth, promptsHeight));
    itemsPanel.setPreferredSize( new Dimension(promptsWidth, promptsHeight));

    completionPanel.setMinimumSize( new Dimension(20, 30) );
    categoryPanel.setMinimumSize( new Dimension(20, 30) );
    itemsPanel.setMinimumSize( new Dimension(20, 30) );


    promptsPanel.add( completionPanel );
    promptsPanel.add( categoryPanel );
    promptsPanel.add( itemsPanel );
    

    //-------------- Status information  --------------
    JLabel label = new JLabel(i18n.getString("Status"));

    // layout the label that reports the status ("ok", "bad") of the text
    statusText = new JLabel(i18n.getString("ok"));

    errorText = new JLabel("");

    label.setBorder
      ( BorderFactory.createEmptyBorder(0, 0, 0, 3)); // top, left, bottom, right
    statusText.setBorder( BorderFactory.createEmptyBorder(0,0,0,5));

    statusBar = new JPanel();
    statusBar.setLayout( new BoxLayout(statusBar, BoxLayout.X_AXIS) );

    statusBar.add(label);
    statusBar.add(statusText);


    //------ Provision for the Unicoder

    statusAndUnicoder = new JPanel();
    statusAndUnicoder.setLayout( new BorderLayout() );

    statusAndUnicoder.add(statusBar, BorderLayout.WEST);
    statusAndUnicoder.add(errorText, BorderLayout.CENTER);



   
    //--------- Put it all together -----------------

    getContentPane().setLayout( new BorderLayout() );

    getContentPane().add(toolBarAndOther, BorderLayout.NORTH);

    splitter = 
      new JSplitPane( JSplitPane.VERTICAL_SPLIT,
		      textscroller, promptsPanel);
    //splitter.setDividerLocation(percentageToText); 
    // Doesn't work because of jdk bug see hack in pack below
    splitter.setOneTouchExpandable( true );

    getContentPane().add(splitter, BorderLayout.CENTER);
    getContentPane().add(statusAndUnicoder, BorderLayout.SOUTH);    

    resizer = new ResizeListener();
    addComponentListener( resizer );


    //----  Handle the close widget in the upper right of the window
    closingAdapter = new myWindowAdapter();
    addWindowListener(closingAdapter);

    setJMenuBar(createMenuBar());

    populated = true;
  }



  class myWindowAdapter extends WindowAdapter {
    @Override
    public void windowClosing (WindowEvent we) {
      shutdown();
    }
  }

  /*
   * Hack to work around Sun Bug: 4101306, They
   * claim it's fixed in 1.2fcs. But it isn't.
   * setDividerLocation computes the actual location
   * at the time of call and has no deferred action.
   * Calling it before the components are laid out
   * sets the splitter at 0.
   */
  @Override
  public void pack () {
    super.pack ();
    splitter.setDividerLocation (percentageToText); 
    // should be on first setBounds. But we always call pack.
  }

  void setSplit(double ratio) {
    splitter.setDividerLocation(ratio);
  }


  class ResizeListener extends ComponentAdapter {
    @Override
    public void componentResized(ComponentEvent e) {
      splitter.setDividerLocation (percentageToText);
    }
  }


  /* This exists just because I can't figure out how to access the
   * session instance variable from within the anonymous class that
   * provides the windowClosing method. */
  private void shutdown() {
    session.shutdownSession(false);
  }


  private JPanel makePromptPanel(String title, PromptView list) {
    JPanel p = new JPanel();
    p.setLayout( new BorderLayout() );

    p.add( new JLabel(i18n.getString(title)), BorderLayout.NORTH );

    JScrollPane scroller = new JScrollPane();
    scroller.getViewport().add( list );
    p.add( scroller, BorderLayout.CENTER );
    
    return p;
  }



  /** 
   * The following methods are used for creating 
   * the menu and adding commands to it
   */

  private CMenuBar mb;
  public CMenuBar getCMenuBar() { return mb; }

  private CMenuBar createMenuBar() {
    mb = new CMenuBar();
    mb.add(createSessionMenu());
    mb.add(createEditMenu());
    mb.add(createViewMenu());
    return mb;
  }

  private CMenu createSessionMenu() {
    CMenu menu = new CMenu(commands.getString("G2TextEditorSessionMenu"));
    export = new ExportCommands(this, session, editor);
    menu.add(export, ExportCommands.LOAD);
    menu.add(export, ExportCommands.SAVE);
    //menu.addSeparator();
    //menu.add(export, ExportCommands.PRINT);
    menu.addSeparator();
    menu.add(sessionHandler, SessionCommands.APPLY_AND_EXIT);
    menu.add(sessionHandler, SessionCommands.APPLY);
    menu.addSeparator();
    menu.add(sessionHandler, SessionCommands.EXIT);
    return menu;
  }

  private CMenu createEditMenu() {
    CMenu menu = new CMenu(commands.getString("G2TextEditorEditMenu"));
    menu.add(editHandler);
    return menu;
  }

  private CMenu createViewMenu() {
    CMenu menu = new CMenu(commands.getString("G2TextEditorViewMenu"));
    view = new ViewCommands(this, session, editor);
    menu.add(view, ViewCommands.UNICODE);
    //menu.add(view, ViewCommands.FONTCHOOSER);  not yet working
    menu.add(view, ViewCommands.TOOLBAR);
    menu.add(view, ViewCommands.LANGUAGEPROMPTS);
    menu.add(view, ViewCommands.ITEMS_AND_NAMES);
    menu.add(view, ViewCommands.STATUS);
    menu.add(view, ViewCommands.LINEWRAP);
    return menu;
  }





  //---- Tool Bar
  
  private ToolBar createToolBar() {
    ToolBar tb = new ToolBar();
    addSessionCommandsToolBarButtons(tb);  
    tb.addSeparator();
    addEditCommandsToolBarButtons(tb);
    return tb;
  }

  private void addSessionCommandsToolBarButtons(ToolBar toolBar) {
    sessionHandler = new SessionCommands(this, session);
    toolBar.add(sessionHandler, SessionCommands.EXIT);
    toolBar.addSeparator();
    toolBar.add(sessionHandler, SessionCommands.APPLY_AND_EXIT);
    toolBar.add(sessionHandler, SessionCommands.APPLY);
  }

  private void addEditCommandsToolBarButtons(ToolBar toolBar) {
    editHandler = new EditCommands(session, (G2EditorWithUndo)editor );
    toolBar.add(editHandler);
  }




  //----- Setup code for the Unicode Inserter -------

  private boolean unicodeInserterIsInstalled = false;
  boolean UnicodeWidgetInstalled() { return unicodeInserterIsInstalled; }

  JPanel unicodePanel;
  UnicodeInserter unicoder;
  UnicodeInserter.UnicodeEntryField unicodeEntryField;

  private void makeUnicodePanels() {
    unicoder = session.getUnicodeInserter();
    unicodeEntryField = unicoder.getEntryField();
    unicodePanel = new JPanel();
    unicodePanel.setLayout( new BoxLayout(unicodePanel, BoxLayout.X_AXIS) );
    unicodePanel.add( new JLabel(i18n.getString("Unicode")) );
    unicodePanel.add( unicodeEntryField );
  }

  void installUnicodeWidget() {
    if ( unicodePanel == null )
      makeUnicodePanels();
    statusAndUnicoder.add(unicodePanel, BorderLayout.EAST);
    validate();
    unicodeEntryField.requestFocus();
    unicodeInserterIsInstalled = true;
  }
       
  void removeUnicodeWidget() {
    if ( unicodeInserterIsInstalled ) {
      statusAndUnicoder.remove(unicodePanel);
      validate();
      requestFocus();
      unicodeInserterIsInstalled = false;
    }
  }
  

  //----- Setup code for the Font Chooser -------

  private boolean fontChooserInitialized = false; // local for the setup
  boolean fontChooserIsVisible = false; // for use by ViewCommands
  FontChooser fontChooser;
  JTextComponent fontChooserTextField;
  JPanel fontChooserUI;
  
  void installFontChooser() {
    if ( !fontChooserInitialized ) {
      if ( fontChooser == null )
	fontChooser = session.getFontChooser();
      fontChooserTextField = fontChooser.getTextComponent();
      if ( fontChooserTextField == null )
	fontChooser.setTextComponent((JTextComponent)editor);
      if ( fontChooserUI == null )
	fontChooserUI = fontChooser.getUI();
      fontChooserInitialized = true;
    }
    addFontChooser();
  }

  void addFontChooser() {
    if ( gotoLineIsVisible )
      removeGoToLineUI();
    toolBarAndOther.add(fontChooserUI, BorderLayout.EAST);
    validate();  // will two validates in quick succession be invisible?
    fontChooserIsVisible = true;
  }

  void removeFontChooser() {
    toolBarAndOther.remove(fontChooserUI);
    validate();
    fontChooserIsVisible = false;
    view.makeFontChooserUnselected();
  }
    

  //----- Setup code for Go To Line ------
  boolean gotoLineIsVisible = false;
  GoToLine goTo;  // "goto" is reserved
  JPanel gotoLineUI;

  void installOrGoToLine() {
    if ( goTo == null ) {
      goTo = new GoToLine( (JTextComponent)editor );
      gotoLineUI = goTo.getUI();
    }
    addGoToLine();
  }

  void addGoToLine() {
    if (fontChooserIsVisible)
      removeFontChooser();
    toolBarAndOther.add(gotoLineUI, BorderLayout.EAST);
    validate();
    gotoLineUI.requestFocus();
    gotoLineIsVisible = true;
  }

  void removeGoToLineUI() {
    toolBarAndOther.remove(gotoLineUI);
    validate();
    gotoLineIsVisible = false;
  }

  

  //---- Cleanup

  @Override
  public void dispose() {
    /* The ViewCommands menu uses checkboxes, and it appears that this
     * causes a set of tables to be setup that never released for 
     * garbage collection, with the indirect result that entire sessions
     * are not released. By cutting off the link between the view object
     * and the session we at least can markedly reduce the amount of
     * stuff that is retained indefinitely and shrink the amount that
     * is leaked.
     */
    //super.dispose();
    //removeBackPointers();
  }

  void removeBackPointers() {
    sessionHandler.removeBackPointers();
    sessionHandler = null;
    editHandler.removeBackPointers();
    editHandler = null;
    export.removeBackPointers();
    export = null;
    view.removeBackPointers();
    view = null;
    ((TextView)editor).removeBackPointers();
    editor = null;
    session = null;
    promptManager = null;
    statusManager = null;
    unicoder = null;
    fontChooser = null;
    goTo = null;

    removeComponentListener( resizer );
    resizer = null;

    removeWindowListener(closingAdapter);
    closingAdapter = null;

    transferFocus();
  }
  
 
}
