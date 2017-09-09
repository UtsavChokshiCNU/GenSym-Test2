/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Session.java
 *
 */
package com.gensym.editor.text;


import java.awt.Cursor;
import java.awt.Frame;
import java.awt.print.PrinterJob;
import java.awt.print.Printable;
import java.awt.Component;
import java.awt.Rectangle;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.nio.charset.Charset;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Closeable;
import java.util.Vector;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
import javax.swing.JFileChooser;
import javax.swing.JTextArea;

import com.gensym.core.GensymApplication;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.SelectionDialog;
import com.gensym.dlg.ErrorDialog;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.ConnectionNotAliveException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.CorruptionException;
import com.gensym.util.UnexpectedException;


/** A text editing Session is instantiated whenever the Text Editor
 * is envoked. It instantiates all the needed widgets and establishes
 * their interconnections. 
 * @author David McDonald
 * @version 5/00
 * @undocumented -- final Text Editor API is still under review
 */

public class Session implements StandardDialogClient, ParsingStatusUpdatedListener, ItemListener {

  private final boolean debug = false;

  private final boolean includeRecorder = false;


  //---- Variables, etc. coordinating reusing editor sessions ----------------------

  private boolean active = true;
  public void setActive(boolean b) { active = b; }
  public boolean getActive() { return active; }

  private int index = -1;
  public void setIndex(int i) { index = i; }
  public int getIndex() { return index; }

  @Override
  public String toString() {
    String s = "#<Session " + index + " ";
    if (active)
      s += "Active";
    else
      s += "available";
    s += ">";
    return s;
  }


  private static volatile Vector editorPool = new Vector(5);
  /**
   * @undocumented
   * @return a <code>Vector</code> of <code>Session</code> objects.
   */
  public static Vector getEditorPool() { return editorPool; }
  /**
   * @undocumented
   */
  public static void setEditorPool(Vector v) { editorPool = v; }




  /** Resources */
  private static final String shortResource = "CommandShortResource";
  private static Resource shortBundle =
     Resource.getBundle("com.gensym.editor.text.CommandShortResource");
  private static Resource i18n = 
     Resource.getBundle("com.gensym.editor.text.TextEditorLabels");


  //---- Core variables ------

  private Item item;       
  /** Returns the item that owns the attribute being edited.  */
  public Item getItem() { return item; }
  /** Sets the item whose attribute is to be edited. */
  public void setItem(Item item) { this.item = item; }


  private Symbol attributeName;
  /** Returns the name of the attribute being edited.  */
  public Symbol getAttributeName() { return attributeName; }
  /**  Sets the name of the attribute to be edited. */
  public void setAttributeName(Symbol n) { attributeName = n; }


  private Symbol grammarCategory;
  /** Returns the name of the category in G2's grammar that the text
   * is being checked against for syntactic correctness. */
  public Symbol getGrammarCategory() { return grammarCategory; }
  /** Sets the name of the category that is to govern the syntactic checking
   * and prompting that the parser does. */
  public void setGrammarCategory(Symbol c) { grammarCategory = c; }


  private Symbol className;
  /** Returns the name of the class that has the attribute being
   * edited. */
  public Symbol getClassName() { return className; }
  /** Sets the name of the G2 class that will have the attribute being edited. */
  public void setClassName(Symbol n) { className = n; }


  private Boolean editingForRuntimeChange = Boolean.FALSE;  // default
  /** Returns whether the results of this edit should be considered
   * permanent (FALSE) or instead the prior value of the attribute should
   * be noted in the KB so that it can be reverted (TRUE). */
  public Boolean getEditingForRuntimeChange() { return editingForRuntimeChange; }
  /** Sets the parameter that determines whether the edit is permanent (FALSE)
   * or revertable (TRUE). */
  public void setEditingForRuntimeChange(Boolean b) { editingForRuntimeChange = b; }


  private TwAccess connection;   
  /** Returns the connection to the G2 that owns the item that is being edited */
  public TwAccess getConnection() { return connection; }
  /** Sets the connection, which should be a connection to the G2 on which
   * the item to be edited resides.  */
  public void setConnection(TwAccess connection) { this.connection = connection; }

    


  //----- The parser interface that we're connected to  --------

  private G2SideParser parser = null;
  /** Returns the object that mediates between this Session on the client
   * and the G2 server that the item being edited is connected to. 
   * The actual parsing is done on the server. */
  public G2SideParser getParser() { 
    if (parser == null)
      parser = new G2SideParser();
    return parser; 
  }
  /** Sets the object that is to mediate the editing session. */
  public void setParser(G2SideParser p) { parser = p; }






  //------ Components of the session's UI -----------

  /* Records whether we are running the UI with the standard set of
   * components and options (e.g. see G2TextEditor), or are just
   * setting up the parsing context with the UI and other connections
   * set up by the caller.  Unclear as yet whether this fact would
   * be of interest to other components/widgets. */
  private boolean standardUI = false;

  private G2TextEditor frame = null;
  /** Gets the Frame that contains the widgets that collectively
   * constitute the text editor.  */
  public G2TextEditor getFrame() { 
    if (frame == null)
      frame = new G2TextEditor();
    return frame;
  }
  /** Sets the Frame that contains the widgets that collectively
   * constitute the text editor.  */
  public void setFrame (G2TextEditor f) { frame = f; }



  private G2Editor editor;
  /** Sets the editing component to be used in this editing session. */
  public void setEditor(G2Editor v) { editor = v; }
  /** Returns the editing component that is used for input of the 
   * keystrokes and mouse gestures that constitute the editing actions 
   * of the session. */
  public G2Editor getEditor() {
    if ( editor == null ) {
      if ( standardUI )
	editor = new TextView( this );
      else
	editor = new G2EditorAdapter();
    }
    return editor;
  }


  /* When we can get the text off the attribute we stash it here
   * to facilitate resets and getting G2 off to the right start.
   * See editor.resetText.  */
  String originalText = "";

  /* This is needed to allow G2SideParser to be defined without reference to
   * TextView. It needs to see the text being edited as part of its Hack #2,
   * where it checks to see whether the error that the parser has just detected
   * involved the cursor being within a string. The error is spurious in the
   * first place, and a fix to the parser would be the correct way to really
   * address it, in which case this hack, and thus this indirect access should
   * be flushed. On the other hand prompting some of the editor component's basic
   * accessors to this level via a delegate might not be a bad idea in general. */
  String getText() { 
    if (editor == null) 
      return "";
    return editor.getText();
  }



  private PromptManager promptManager = null;  
  // mediates updates to and display of the prompts
  void setPromptManager(PromptManager m) { promptManager = m; }
  PromptManager getPromptManager() { 
    if (promptManager == null) {
      promptManager = new PromptManager(connection, this);
      setPromptView( promptManager.getCompletionView() );
      setCategoryView( promptManager.getCategoryView() );
      setCategoryTokensView( promptManager.getCategoryTokensView() );
    }
    return promptManager;
  }

  private CategoryView categoryView;
  /** Returns the widget in which the category prompts are displayed. */
  public CategoryView getCategoryView() { return categoryView; }
  /** Sets the widget to be used to display the category prompts. */
  public void setCategoryView(CategoryView c) { categoryView = c; }


  private PromptView completionView;
  /** Returns the widget in which the token prompts are displayed.*/
  public PromptView getPromptView() { return completionView; }
  /** Sets the widget to be used to display the token prompts. */
  public void setPromptView(PromptView v) { completionView = v; }


  private PromptView categoryTokensView;
  /** Returns the widget in which instances of a selected category prompt 
   *  are displayed. */
  public PromptView getCategoryTokensView() { return categoryTokensView; }
  /** Sets the widget to be used to display instances of selected category 
   * prompts. */
  public void setCategoryTokensView(PromptView p) { categoryTokensView = p; }
  


  private StatusManager statusManager = null;  
  // mediates updates to and display of the status 
  void setStatusManager(StatusManager m) { statusManager = m; }
  StatusManager getStatusManager() { 
    if (statusManager == null) 
      statusManager = new StatusManager();
    return statusManager;
  }


  private SearchAndReplaceManager searchMgr;

  private G2ConnectionAdapter closingAdapter;



  private JLabel statusText;
  /** Returns the widget used to present the text that indicates whether the parse
   * is 'ok' or 'bad'. */
  public JLabel getStatusText() { return statusText; }
  /** Set the widget to be used to present the status of the text. */
  public void setStatusText(JLabel status) { statusText = status; }


  private JLabel errorText;
  /** Returns the widget used to present the String that indicates what's wrong
   * with the text if it is ungrammatical. */
  public JLabel getErrorText() { return errorText; }
  /** Set the widget to be used to present the String that indicates what's wrong. */
  public void setErrorText(JLabel err) { errorText = err; }


  private UnicodeInserter unicoder;
  public void setUnicodeInserter(UnicodeInserter u) { unicoder = u; }
  public UnicodeInserter getUnicodeInserter() {
    if ( unicoder == null ) {
      unicoder = new UnicodeInserter( this );
      return unicoder;
    }
    else 
      return unicoder;
  }



  /* This variable is true if changes have been made to the text
   * that have not yet been applied and concluded into the object
   * being edited. */
  private transient boolean dirtyBit;
  void setDirtyBit () { dirtyBit = true; }
  void clearDirtyBit () { dirtyBit = false; }
  public boolean theTextIsDirty() { return dirtyBit; }

  /* This is made when in development mode. It allows the ParserInputEvents
   * to be recorded and played back. */
  private transient RecordEditorEvents recorder;


  private FontChooser fontChooser;
  /** Returns the instance of a FontChooser associated with this
   * session. If there is none at the time this is called a new
   * one is created that is not associated with any editing field. */
  public FontChooser getFontChooser() { 
    if ( fontChooser == null ) {
      fontChooser = new FontChooser();
    }
    return fontChooser; 
  }
  /** Set the FontChooser to be used in this session. The FontChooser
   * is expected to already be associated with its target editing
   * field. */
  public void setFontChooser(FontChooser c) { fontChooser = c; }




  //----------- Constructors -------------

  public Session () {}


  // Symbols used by the next constructor
  private static final Symbol CLASS_ = Symbol.intern ("CLASS");
  private static final Symbol TEXT_  = Symbol.intern ("TEXT");
  private static final Symbol TYPE_  = Symbol.intern ("TYPE");
  private static final Symbol EDITOR_GRAMMAR_ = Symbol.intern ("EDITOR-GRAMMAR");
  private static final Symbol ATTRIBUTE_NAME_ = Symbol.intern ("ATTRIBUTE-NAME");

  /* Obsolete. Use Session(Item, Symbol).
   * @deprecated The classQualifier argument is no longer used.
   */
  public Session(Item item, Symbol attributeName, Symbol classQualifier) {
    this(item, attributeName);
  }

  /** Normal way of initiating an editing session.
   *@param item The item with the attribute that will be edited.
   *@param attributeName A symbol naming the attribute to be edited.
   */
  public Session(Item item, Symbol attributeName) {
    this(item, attributeName, true);
  }

  /** Permits the creation of a session with custom UI.
   *@param item The item with the attribute that will be edited.
   *@param attributeName A symbol naming the attribute to be edited.
   *@param useStandardUI If true, the standard UI is launched. If false, no
   * UI is automatically created but the user may implement their own.
   */
  public Session(Item item, Symbol attributeName, boolean useStandardUI) {
    initialize(item, attributeName, useStandardUI);
  }
  public void initialize(Item item, Symbol attributeName, boolean useStandardUI) {
    this.item = item;
    this.attributeName = attributeName;
    standardUI = useStandardUI;

    if (useStandardUI) {
      /* Going over the network to get the parsing context and
       * such is the most time-consuming activity in setting up 
       * an editing session, so we need to throw up the Wait Curor
       * this early if it is to be at all useful. */
      frame = getFrame(); // just the component so the cursor
      putupWaitCursor();          // has something to ride on.
    }

    connection = getItemContext(item);
    className = getItemsClassName(item);
    if (attributeName == null) {
      throw new IllegalArgumentException("No value provided for specificAttributeName");
    }

    if ( !handleThisOutsideTheEditor(originalText) ) {
      /* The 'outside the editor' is now for text-stripped attributes, but could 
       * be a hook for other odd types that the Classic Editor accomodates that
       * don't really involve parsing. */

      parser = establishParsingSession(connection, item, className, attributeName);

      if (useStandardUI) {
	constructTheStandardUI(frame);
	exposeTheStandardUI(frame);
	putupDefaultCursor();
      }
    }
  }


  //----- Subroutines for establishing the standard session/UI -------

  protected TwAccess getItemContext(Item item) {
    return (TwAccess)((ImplAccess)item).getContext();
  }

  protected Symbol getItemsClassName(Item item) {
    Symbol name = CLASS_; // provide the compiler with a default
    try { 
    	name = item.getG2ClassName();
    } catch (G2AccessException e) {
      throw new UnexpectedException(e, "Error while getting class name");
    }
    return name;
  }

  protected String getAttributesText(Item item, Symbol attributeName) {
    String text = "";
    try {
      Sequence attrSeq = new Sequence (1);
      attrSeq.addElement(attributeName);
      Structure attrTexts = ((ImplAccess)item).getAttributeTexts (attrSeq);
      text = (String) attrTexts.getAttributeValue (attributeName, null);
    } catch (G2AccessException g2ae) {
      throw new CorruptionException(g2ae, "Unable to download text of attribute");
    }
    if (text == null)
      text = "";
    return text;
  }

  /* Once the interface that defines a parser has been sorted out this
   * return value should be changed to it so that we can make changes
   * for experiments with client-side parsing/tokenizing without always 
   * having to revisit Session. */
  protected G2SideParser establishParsingSession (TwAccess connection, 
						  Item item,
						  Symbol className, 
						  Symbol attributeName) {
    G2SideParser p = openParsingSession(connection, className, attributeName);

    /* The parsing context is the handle used by the G2-side parser to 
     * indicate the structure it has corresponding to this editing session.
     * We wouldn't need to expose it outside of G2SideParser except that the
     * original design of this interface didn't make provisions for passing
     * the item through on the call set up the G2-side context, and, looking
     * forward, because the rpc used here will need to exist as part of 
     * client-side editing, whereas all the other work done in G2SideParser
     * will not. */
    Integer parsingContext = p.getParsingContext();
    try { 
    	connection.sendItemToG2SideEditingContext(item, parsingContext);
    } catch (ConnectionNotAliveException e) {
      /* Placeholder: When we have implemented a 'save this session' capability,
       * we would give the user the option to do that at this point. */
    } catch (G2AccessException e) {
      Trace.exception(e, "problem initializing the item in the parsing context");
    }
    return p;
  }


  /** Creates a parsing session on the connected G2 by creating a G2SideParser
   * object to mediate ParserInputEvent transactions. Note that there is no
   * item associated with this parsing session, only the grammar of the specified
   * attribute of the specified class.
   */
  public G2SideParser openParsingSession(TwAccess connection, Symbol className,
					 Symbol attributeName) {
    if (debug)
      System.out.println("Opening a parsing session over " + connection +
			 "\n  for the " + attributeName + " of a " + className);
    G2SideParser p = getParser();
    p.initializationsForStandardSetup(connection, this, className, attributeName);
    if ( ! p.setupWasSuccessful() ) {
      throw new IllegalArgumentException("Invalid attribute or class");
    }
    return p;
  }




  protected void constructTheStandardUI (G2TextEditor frame) {
    if ( editor == null )
      editor = new TextView( this );

    determineLineWrapPolicy();

    // This does not yet work -- all of the machinery is in place
    // except for finding a means of actually changing the font.
    //fontChooser = new FontChooser();
    //fontChooser.initialize( (JTextComponent)editor );

    getPromptManager();
    // we need a promptManager before we populate the UI because it supplies
    // the views that UI methods will access.

    applyTheFocusHackIfNecessary();

    if (!frame.getPopulated())
      frame.populateG2TextEditor(this);
    frame.setTitle( i18n.format("titlebar", attributeName, className) );

    getStatusManager();
    
    if (includeRecorder) {
      if ( GensymApplication.getDevOption() )
	initializeSessionRecorder();
    }

    establishListeners();
    initializeState();
  }

  protected void exposeTheStandardUI(G2TextEditor frame) {
    if(isHP) {
      // This HP stuff is an ugly hack to deal with
      // problems to do with "pack". This bug is tracked
      // internally as:
      // HQ-3389046: Caret misplaced in TextEditor on HP
      // For some reason, the setSize needs to be called
      // before and after the setVisible. I am hurrying this
      // a little bit, so it's possible a better hack is available.
      // rpenny 3/7/00
      // The "pack" is left for other platforms.
      frame.setSize(400, 361);
    } else
      frame.pack();

    centerFrame (frame);
    frame.setVisible( true );
    if(isHP) {
      frame.setSize(400, 360);
      frame.setSplit(.6);
    }
  }
  




  //----- Hacks to get around problems -------
  private static boolean isHP;

  // This boolean is only needed as part of the following focus hack.
  private static boolean isWindows;
  static {
    String osName = System.getProperty("os.name");
    if (osName == null) {
      isWindows = false;
      isHP = false;
    } else {
      String lowerCase = osName.toLowerCase();
      isWindows = lowerCase.indexOf("windows") != -1;
      isHP = lowerCase.indexOf("hp") != -1;
    }
  }

  /**
   * This hack is a workaround for Swing bug #
   * 4293388: JSplitPane has problems with setting focus.
   * If that bug is fixed, get rid of this hack. Note that the
   * isWindows field should also no longer be necessary.
   */
  private boolean focusHackApplied = false;

  private void applyTheFocusHackIfNecessary() {
    //if (!isWindows) -- lost history! What motivates applying this
    //                   regardless of the O/S ?
    if (!focusHackApplied)
      frame.addComponentListener(new FocusHackAdapter());
    focusHackApplied = true;
  }

  

  private class FocusHackAdapter extends ComponentAdapter {
    private Runnable focusHack = new FocusHack((Component)editor, 
					       promptManager.getCompletionView());
    @Override
    public void componentResized(ComponentEvent e) {
      SwingUtilities.invokeLater(focusHack);
    }
  }
      
  private class FocusHack implements Runnable {
    private Component shouldHaveFocus;
    void setShouldHaveFocus(Component c) { shouldHaveFocus = c; }
    private Component theOtherGuy;
    void setTheOtherGuy(Component c) { theOtherGuy = c; }

    FocusHack(Component shouldHaveFocus, Component theOtherGuy) {
      this.shouldHaveFocus = shouldHaveFocus;
      this.theOtherGuy = theOtherGuy;
    }

    @Override
    public void run() {
      theOtherGuy.requestFocus();
      shouldHaveFocus.requestFocus();
    }
  }


  private static java.awt.Dimension screenDisplaySize
  = java.awt.Toolkit.getDefaultToolkit().getScreenSize ();

  private static final int dialogMargin = 25;

  private void centerFrame (java.awt.Window win) {
    Frame theFrame = com.gensym.core.UiApplication.getCurrentFrame ();
    if (theFrame == null)
      return;
    Rectangle frameBnds = theFrame.getBounds ();
    Rectangle dlgBounds = win.getBounds ();
    int dlgWidth        = dlgBounds.width;
    int dlgHeight       = dlgBounds.height;
    int dlgX = frameBnds.x + (frameBnds.width - dlgWidth)/2;
    int dlgY = frameBnds.y + (frameBnds.height - dlgHeight)/2;
    if (dlgX + dlgWidth > screenDisplaySize.width)
      dlgX = screenDisplaySize.width - dialogMargin - dlgWidth;
    if (dlgY + dlgHeight > screenDisplaySize.height)
      dlgY = screenDisplaySize.height - dialogMargin -dlgHeight;
    if (dlgX < 0)
      dlgX = dialogMargin;
    if (dlgY < 0)
      dlgY = dialogMargin;
    win.setBounds (dlgX, dlgY, dlgBounds.width, dlgBounds.height);
  }


  private void queryUserForAttributeName()
  {
    try {
      Sequence attrDescrpns = item.getAttributeDescriptions();
      Sequence attrNames = new Sequence();
      for (java.util.Enumeration e = attrDescrpns.elements(); e.hasMoreElements();) {
	Structure attrDescprn = (Structure)e.nextElement();
	if (debug)
	  System.out.println("DDM: for element: " +
			     attrDescprn.getAttributeValue(ATTRIBUTE_NAME_, null) +
			     "\n       The attributes are: " + attrDescprn.toString());
	java.lang.Object grammar = attrDescprn.getAttributeValue(EDITOR_GRAMMAR_, null);
	if (grammar != null)
	  attrNames.addElement(attrDescprn.getAttributeValue(ATTRIBUTE_NAME_, null)
			       .toString());
      }
      if (debug)
	System.out.println ("\nAttribute Names = " + attrNames);
      
      String[] attrNamesArray = new String[attrNames.size()];
      attrNames.copyInto(attrNamesArray);
      SelectionDialog osd = new SelectionDialog (frame, "Edit Attribute",
						 true,
						 "Choose Attribute To Edit",
						 attrNamesArray,
						 false,
                                                 -1,
						 true,
						 null);
      osd.setVisible(true);
      int selectedIndex = osd.getResult();
      if (selectedIndex < 0)
	return;
      String attrName = attrNamesArray[selectedIndex];
      attributeName = Symbol.intern(attrName);
      
    } catch (G2AccessException e) {
      com.gensym.message.Trace.exception (e, "Error while getting editable attributes");
      if (debug)
	System.out.println("DDM: Error while getting editable attributes");
      return;
    }

  }




  private boolean listenersHaveBeenEstablished = false;

  /* This one is used when G2TextEditor is being used since
   * many of the linkups are done over there. */
  void establishListeners() {
    if (!listenersHaveBeenEstablished) {
      parser.addParsingStatusUpdatedListener( editor );
      parser.addParsingStatusUpdatedListener( statusManager );
      parser.addParsingStatusUpdatedListener( this );
      parser.addPromptsUpdatedListener( promptManager );
      
      if (includeRecorder) {
	if ( GensymApplication.getDevOption() ) {
	  parser.addParsingStatusUpdatedListener(recorder);
	  /* The recorder has to get on the Input Event listener list before
	   * the parser does. Otherwise, the a change in status to 'bad' will
	   * come out of the parser and 'dump' the recording before the
	   * event that triggered the change is recorded.  --This sounds
	   * very un-Java like to know this much about how things are
	   * implemented, but I don't know another way to do it if the
	   * dumping operation is to be automatic. */
	  editor.addParserInputEventListener(recorder);
	}
      }
      editor.addParserInputEventListener(parser);
      
      categoryView.addListSelectionListener( promptManager );
      completionView.addListSelectionListener( promptManager );
      categoryTokensView.addListSelectionListener( promptManager );
      promptManager.setTargetView( editor );

      /* Push these objects into the StatusManager */
      statusManager.setStatusText( frame.getStatusText() );
      statusManager.setErrorText( frame.getErrorText() );
      
      connection.addG2ConnectionListener 
	(closingAdapter = new G2ConnectionAdapter () {
	  @Override
	  public void g2ConnectionClosed (G2ConnectionEvent cxnEvent) {
	    dirtyBit = false;
	    // Amend this to give them a real message and the option
	    // to save their work to a file !!!!!!!!!!!!!!!!!!!!!!!1
	    shutdownSession (false);
	  }
	});

      listenersHaveBeenEstablished = true;
    }

    try { 
    	item.addItemListener(this);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }

  }



  /* RemoveListeners is part of the removeBackPointers facility. */
  void removeListeners() {
    parser.removeParsingStatusUpdatedListener( editor );
    parser.removeParsingStatusUpdatedListener( statusManager );
    parser.removeParsingStatusUpdatedListener( this );
    parser.removePromptsUpdatedListener( promptManager );
    editor.removeParserInputEventListener( parser );
    categoryView.removeListSelectionListener( promptManager );
    completionView.removeListSelectionListener( promptManager );
    categoryTokensView.removeListSelectionListener( promptManager );
  }





  void initializeState() {
    /* See the PromptManager's view with prompts. */
    parser.issueInitialPrompts();

    // Get the text into the View.  Later also position the cursor.
    // N.b. this makes a call out to the parser.
    originalText = getAttributesText(item, attributeName);
    editor.setText(originalText, 0);

    // We haven't changed anything yet, so set up the state of the
    // apply command and the dirty bit accordingly.
    clearDirtyBit();
    deactivateApplyService();
  }




  private static final Symbol PROCEDURE_  = Symbol.intern("PROCEDURE");

  private void determineLineWrapPolicy() {
    if ( (className.equals(PROCEDURE_))
	 && (attributeName.equals(TEXT_))) {
      /* n.b. 'editor' is just defined against an interface */
      JTextArea editorPrime = (JTextArea)editor;
      editorPrime.setLineWrap( false );
      /* The default is to wrap. */
    }
  }





  /* reworking in progress */
  private void initializeSessionRecorder() {
    //recorder = new RecordEditorEvents(editor, this);
    //recorder.initialize();
  }






  //----------- Loading/Saving the text being edited

  /* This is called from the menu-item handler in SessionCommands. */
  void selectAndLoadFileIntoEditor () {
    JFileChooser chooser = new JFileChooser();
    int returnValue = chooser.showOpenDialog( frame );
    if ( returnValue == JFileChooser.APPROVE_OPTION ) {
      File f = chooser.getSelectedFile();
      try { 
    	  loadFileIntoEditor(f);
      } catch (FileNotFoundException e) {
	ioProblem1("ioFNF", f.toString());
      } catch (IOException e) {
	ioProblem1("loadIOExcp", e.toString());
      } 
    }
  }

  void loadFileIntoEditor( File f ) throws IOException, FileNotFoundException {
    String text = "";
    FileInputStream inStream = null;
    Reader reader = null;
    BufferedReader b = null; 
    try {
      inStream = new FileInputStream(f);	
      reader = new InputStreamReader(inStream, Charset.defaultCharset());
      b = new BufferedReader(reader);
      String line = b.readLine();
      text = line;
      for (;;) {
	line = b.readLine();
	if (line == null)
	  break;
	text = text + "\n" + line;
      }
      if ( text != null ) {
	originalText = text;
	initializeState();
      }
    } finally {
  	  closeSilently(b);
	  closeSilently(reader);
	  closeSilently(inStream);
    }
  }
  
  private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  ioProblem1("ioClose", obj.toString());
      } 
  }

  void saveEditorTextToFile () {
    JFileChooser chooser = new JFileChooser();
    int returnValue = chooser.showOpenDialog( frame );
    if ( returnValue == JFileChooser.APPROVE_OPTION ) {
      File f = chooser.getSelectedFile();
      try { 
    	  writeTextOfEditorOutToFile(f);
      } catch (FileNotFoundException e) {
	ioProblem1("ioFNF", f.toString());
      } catch (IOException e) {
	ioProblem1("saveIOExcp", e.toString());
      } 
    }
  }

  void writeTextOfEditorOutToFile(File f) throws IOException, FileNotFoundException {
    String text = editor.getText(); // too crude ?
    FileOutputStream outStream = null;
    Writer writer = null;
    BufferedWriter b = null;
    try {
      outStream = new FileOutputStream(f);
      writer = new OutputStreamWriter(outStream, Charset.defaultCharset());
      b = new BufferedWriter(writer);
      b.write(text, 0, text.length());
    } finally {
   	  closeSilently(b);
 	  closeSilently(writer);
 	  closeSilently(outStream);
    }
  }


  private void ioProblem1(String label, String arg1) {
    ErrorDialog d = 
      new ErrorDialog(null, // frame
		      i18n.getString("ioTitle"), // title
		      true, // modal?
		      i18n.getString(label) + arg1, // message
		      null);  // client to handle response
    d.setVisible( true );
  }





  //----------- Printing the text being edited

  void printEditorContents () {
    System.out.println("1");
    PrinterJob printJob = PrinterJob.getPrinterJob();
    printJob.setPrintable((Printable)editor);
    if ( printJob.printDialog() ) {
      try {
	printJob.print();
      } catch (Exception e) {
	e.printStackTrace();
      }
    }
  }



  //------- Abstracting Prompt actions for daughter components ------

  public void clearAllPrompts() {
    promptManager.clearAllPrompts();
  }



  //----- Commands sent here to avoid typing to G2TextEditor

  void installOrGoToLine() {
    frame.installOrGoToLine();
  }





  //----------- Button actions ------------

  /** This removes all of the text from the editor widget, replacing
   * it with the null string and re-initializes the state of the
   * parser.
   * @undocumented -- final Text Editor API is still under review
   */
  public void clearSession() {
    editor.setText("", 0); 
    parser.clearParsingContext();
    setDirtyBit();
    activateApplyService();
  }


  /** This is the cancel-editing action. It can be run at any 
   * time. It closes down the G2-side of the editing session
   * in a nice way and handles any other required internal
   * cleanup. */  
  public void shutdownSession(boolean parserIsShutDown) {
    /* The argument keeps us from looping when there's a Connection
     * NotAlive exception thrown from the parser. */
    if ( dirtyBit )
      launchConfirmCancelDialog();
    else {
      //removeListeners();
      if ( frame != null ) {
	frame.setVisible (false);
	//frame.dispose();
	//frame.getContentPane().remove(frame.splitter);
	//frame = null;
      }
      if ( parser != null ) {
	if ( !parserIsShutDown )
	  parser.shutdownParsingContext();
	//parser.removeBackPointers();
	//parser = null;
      }
      if ( searchMgr != null ) {
	searchMgr.shutdown();
	//searchMgr = null;
      }
      if ( connection != null ) {
	try {
	  //connection.removeG2ConnectionListener (closingAdapter);
	  //closingAdapter = null;
	  item.removeItemListener(this);
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	}
	//connection = null;
      }
      if ( editor != null )
	((TextView)editor).shutdown();
      //removeBackPointers();
    }
    setActive( false );
  }

  private void removeBackPointers() {
    ((TextView)editor).removeBackPointers();
    editor = null;
    promptManager.removeBackPointers();
    promptManager = null;
    statusManager = null;
    categoryView = null;
    completionView = null;
    categoryTokensView = null;
    unicoder.setSession( null );
    unicoder = null;
    fontChooser = null;
  }


  /* This is a placeholder in case we want to throw up a message
   * or something before/as we do this. Presently we can get these
   * from G2SideParser.  */
  public void rugPulledOutFromUnder(ConnectionNotAliveException e) {
    shutdownSession( true );
  }


  public void launchConfirmCancelDialog() {
    QuestionDialog q = new QuestionDialog(frame, "Editor", true, 
				    shortBundle.getString("ApplyChangesBeforeExit"),
				    this);
    q.setVisible( true );
  }

  @Override
  public void dialogDismissed(StandardDialog d, int cmdCode) {
    if (cmdCode == CommandConstants.YES) {
      attemptToConcludeTextThenExit();
    }
    else if (cmdCode == CommandConstants.NO) {
      clearDirtyBit();
      shutdownSession( false );
    }
  }




  /** This will conclude a new value into the attribute being edited
   * provided that the text is currently complete. If the cursor is
   * not already at the end of the text then an additional advance
   * will be sent to G2 causing the remainder of the text to be parsed.
   */
  boolean attemptToConcludeText() {
    boolean ok_P = 
      editor.attemptToConcludeText(item, parser, editingForRuntimeChange);
    if ( ok_P ) {
      clearDirtyBit();
      deactivateApplyService();
    }
    return ok_P;
  }

  /** This attempts to conclude and if it is successful initiates
   * a call to shutdownSession(). */
  void attemptToConcludeTextThenExit() {
    if ( attemptToConcludeText() )
      shutdownSession( false );
  }


  void initiateTextSearchAndReplaceOn(TextSearchTarget editor) {
    if ( searchMgr == null )
      searchMgr = new SearchAndReplaceManager(editor);
    else
      searchMgr.show();
  }

  void initiateReplaceRegionOn(TextSearchTarget editor) {
    new FindAndReplace(editor);
  }



  //----- Watch Cursor ----------

  void putupWaitCursor() {
    frame.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
  }

  void putupDefaultCursor() {
    frame.setCursor(Cursor.getDefaultCursor());
  }



  //-------- Calls that bounce up here before being dispatched to
  //         their real handler ---------------------------------------


  boolean categoryPromptsExist() {
    return (   ( completionView != null )
	    && !completionView.empty() );
  }



  void activateUndoService() {
    fireServiceStateEvent(new ServiceStateEvent(this, ServiceStateEvent.Undo, true));
  }
  void deactivateUndoService() {
    fireServiceStateEvent(new ServiceStateEvent(this, ServiceStateEvent.Undo, false));
  }


  void activateRedoService() {
    fireServiceStateEvent(new ServiceStateEvent(this, ServiceStateEvent.Redo, true));
  }
  void deactivateRedoService() {
    fireServiceStateEvent(new ServiceStateEvent(this, ServiceStateEvent.Redo, false));
  }


  void activateApplyService() {
    fireServiceStateEvent(new ServiceStateEvent(this, ServiceStateEvent.ApplyChanges, true));
  }
  void deactivateApplyService() {
    fireServiceStateEvent(new ServiceStateEvent(this, ServiceStateEvent.ApplyChanges, false));
  }

  void activateLoadService() {
    fireServiceStateEvent( new ServiceStateEvent(this, ServiceStateEvent.Load, true));
  }
  void deactivateLoadService(){
    fireServiceStateEvent( new ServiceStateEvent(this, ServiceStateEvent.Load, false));
  }
			   
  void activateSaveService() {
    fireServiceStateEvent( new ServiceStateEvent(this, ServiceStateEvent.Save, true));
  }
  void deactivateSaveService(){
    fireServiceStateEvent( new ServiceStateEvent(this, ServiceStateEvent.Save, false));
  }
			   
	
	


  /** The method that implements ParsingStatusUpdatedListener. 
   */
  @Override
  public void changeParsingStatus(ParsingStatusUpdatedEvent e) {
    if ( e.statusIsOkQ() )
      fireServiceStateEvent
	(new ServiceStateEvent(this, ServiceStateEvent.GoToError, false));
    else {
      if ( e.validErrorIndex() )
	fireServiceStateEvent
	  (new ServiceStateEvent(this, ServiceStateEvent.GoToError, true));
      else
	fireServiceStateEvent
	  (new ServiceStateEvent(this, ServiceStateEvent.GoToError, false));
    }
  }


  //-------- Support Methods for ServiceStateEvents ---------

  Vector listeners = new Vector();

  public void addServiceStateListener (ServiceStateListener listener) {
    listeners.addElement(listener);
  }

  public void removeServiceStateListener (ServiceStateListener listener) {
    listeners.removeElement(listener);
  }

  public void fireServiceStateEvent (ServiceStateEvent event) {
    int size = listeners.size();
    for (int i=0; i < size; i++) {
      ((ServiceStateListener)(listeners.elementAt(i))).serviceStateChanged(event);
    }
  }

  // BEGIN: ItemListener methods
  @Override
  public void receivedInitialValues (ItemEvent event) {}
  @Override
  public void itemModified (ItemEvent event) {}
  @Override
  public void itemDeleted (ItemEvent event) {
    /* Clear the dirty bit, since if the item is gone, there's no way
     * we can conclude any changes that might be pending. */
    dirtyBit = false; 
    shutdownSession(false);
  }
  // END: ItemListener methods

  



  //--------- Checks for situations that shouldn't be done 
  //          using this editor ----------------------------------

  private boolean handleThisOutsideTheEditor(final String originalText) {
    String text = originalText;
    if (standardUI) {
      text = getAttributesText(item, attributeName);
    }

    return "....".equals(text);  // item has been text-stripped
  }



} // end of the class
