/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 JEditorTest.java
 *
 */
package com.gensym.tests;

import javax.swing.SwingConstants;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JMenuBar;
import javax.swing.JToolBar;
import javax.swing.JSplitPane;
import javax.swing.JTextPane;
import javax.swing.JScrollPane;
import javax.swing.JList;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.ListModel;
import javax.swing.DefaultListModel;
import javax.swing.ListSelectionModel;
import javax.swing.BoxLayout;
import javax.swing.text.JTextComponent;
import javax.swing.text.Element;
import javax.swing.text.Document;
import javax.swing.text.StyledDocument;
import javax.swing.text.DefaultStyledDocument;
import javax.swing.text.AttributeSet;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.BadLocationException;
import javax.swing.text.Caret;
import javax.swing.text.Keymap;
import javax.swing.text.DefaultEditorKit;
import javax.swing.KeyStroke;
import javax.swing.Action;
import javax.swing.border.TitledBorder;
import javax.swing.event.CaretListener;
import javax.swing.event.CaretEvent;

import java.util.Hashtable;
import java.util.Vector;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Event;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.menu.CMenu;
import com.gensym.ui.Command;
import com.gensym.ui.toolbar.ToolBar;

import com.gensym.ntw.TwGateway;
import com.gensym.jgi.G2Access;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

import com.gensym.editor.text.Session;
import com.gensym.editor.text.G2SideParser;
import com.gensym.editor.text.TextView;  // just for EditCommands
import com.gensym.editor.text.EditCommands;
import com.gensym.editor.text.SessionCommands;

import com.gensym.editor.text.PromptsUpdatedListener;
import com.gensym.editor.text.PromptsUpdatedEvent;
import com.gensym.editor.text.PromptsTarget;
import com.gensym.editor.text.PromptManager;

import com.gensym.editor.text.ParserInputEvent;
import com.gensym.editor.text.ParserInputSource;
import com.gensym.editor.text.ParserInputEventListener;


/* History:
 * First developed Winter/Spring 1998 as EditorApp to permit testing
 * the editor when the links to initiate it were still under development.
 *
 * Version 2.0 February/March 1999 -- was used to study how to make
 * the editor lightweight (hence change to JEditorTest to ape the "J"
 * prefixes so that it could display characters outside of ascii.
 * This code exercises most of the facilities of the "J" components
 * and seeds high-order characters in all the places that texts can
 * appear. If the connection is not made with the corresponding fonts
 * these characters appear as boxes (if the character is understood but
 * no gliph is available) or as question marks if the character is not
 * understood, i.e. that location doesn't handle full Unicode.
 *
 * Version 3.0 May 2000 -- Used to test the separation of prompting
 * and editing from the 'standard' setup of the editor. Inner classes
 * for the Document and JTextPane were considerably elaborated and
 * connections to the parser, prompting, and issuing of ParserInputEvents
 * added. 
 */

/** Testing frame for the Text Editor.
 *
 * This allows testing the functionality of the Text Editor without
 * going through T2T to get an item and start a Session.
 *
 * By default this is setup as though you were defining a procedure.
 *
 * The first command line argument is the host, second is the port.
 *
 * Flags:
 *   Prepopulate: introduces styled text in high-order characters
 *     into the editor pane and the prompt view to test these abilities.
 *   listAllAvailableActions:  does that as part of initialization.
 *
 * @author David McDonald
 * @version 3.0 May 2000
 */

public class JEditorTest extends JFrame {

  static final boolean debugConnection = false;
  static final boolean debugPrompts = false;
  static final boolean debugModelAndOutput = false;

  static final boolean listAllAvailableActions = false;

  /* The prepopulate flag will put text into the prompt view and
   * the editor view so it is visible when the frame comes up. 
   * The text is in several languages (Hebrew, CJK) and several 
   * pre-defined styles. */
  static final boolean prepopulate = false;


  JPanel promptsPanel;
  JLabel promptsLabel;
  myJList promptsList;
  DefaultListModel prompts;
  JScrollPane promptsScroller;

  myJTextPane textpane;
  DefaultStyledDocument doc;
  JScrollPane textscroller;

  JSplitPane splitpane;

  Session session;
  G2SideParser parser;
  ToolBar toolbar;
  Command sessionHandler;
  Command editHandler;

  Hashtable allActions;



  public JEditorTest () {
    setTitle("JFrame \u6090 Test");
    BorderLayout frameLayout = new BorderLayout(); // no gaps between items
    getContentPane().setLayout( frameLayout ); // this is the default anyway

    addWindowListener (new java.awt.event.WindowAdapter () {
      @Override
      public void windowClosing (java.awt.event.WindowEvent wEvt) {
	System.exit (2);
      }
    });

    //---- prompts equivalent ---------------
    promptsPanel = constructPromptsPanel();    
    
    //---- text view equivalent ------
    textpane = contructTextPane();
    
    //---- open a session and wire it up
    session = new Session();
    parser = session.openParsingSession(connection, className, attributeName);
    if (debugConnection)
      System.out.println("Opened parsing session via " + parser);

    //---- send text changes to the parser
    textpane.addParserInputEventListener(parser);

    //---- send prompt results from the parser to the prompt list
    parser.addPromptsUpdatedListener(promptsList);

    //---- the textpane can insert selections from the prompts list
    promptsList.addListSelectionListener(textpane);
    
    //---- putting them together -----------
    splitpane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
			       promptsPanel, textscroller);
    splitpane.setOneTouchExpandable(true); // no effect on NT. -- try false!
        
    //---- handlers for session and edit commands
    sessionHandler = new SessionCommands( this, session );
    editHandler = new EditCommands( this, session, new TextView() );

    //---- Add some keybinding after populating the action set
    createActionTable(textpane);
    addKeymapBindings();

    //---- put the toolbar into its own panel that is then folded in with
    //     the text and prompts pane as sisters
    toolbar = constructToolBar();
    getContentPane().add(toolbar, BorderLayout.NORTH);
    getContentPane().add(splitpane, BorderLayout.CENTER);

    // Add a menu to the outermove JFrame
    setJMenuBar( createTextEditorMenuBar() );

    pack();
    show();

  }  // end of constructor



  /* Initializes the editor pane.
   */
  protected myJTextPane contructTextPane() {
    textpane = new myJTextPane();
    textpane.setBorder( new TitledBorder("text") );
    textpane.addCaretListener(textpane);
    
    textscroller = new JScrollPane();
    textscroller.getViewport().add(textpane);
    
    doc = new myDefaultStyledDocument();
    textpane.setDocument(doc);
    initStyles(); // Assigns names to styles and registers them with the textpane
    if ( prepopulate )
      populateTheDocument(); // put some text into the document following the styles
    textpane.initialize();
    
    return textpane;
  }


  /* Initializes the prompts panel.
   */
  protected JPanel constructPromptsPanel() {
    promptsLabel = new JLabel("pro\u6090mpts", SwingConstants.CENTER);
    
    promptsList = new myJList();
    promptsList.initialize();
    if ( prepopulate )
      promptsList.populateCharacterSample();

    promptsScroller = new JScrollPane(promptsList);
    promptsPanel = new myJPanel();
    promptsPanel.setLayout( new BoxLayout(promptsPanel, BoxLayout.Y_AXIS) );
    promptsPanel.setBorder( new TitledBorder("prompts") );
    promptsPanel.add(promptsLabel);
    promptsPanel.add(promptsScroller);

    return promptsPanel;
  }



  private JMenuBar createTextEditorMenuBar() {
    CMenuBar mb = new CMenuBar();
    // the session commands
    CMenu session = new CMenu("fo\u6090o");
    session.add(sessionHandler, SessionCommands.APPLY);
    session.add(sessionHandler, SessionCommands.EXIT);
    mb.add(session);
    return mb;
  }
  protected ToolBar constructToolBar() {
    toolbar = new ToolBar();
    toolbar.add(sessionHandler);
    toolbar.add(editHandler);
    return toolbar;
  }


  //--------------------------------------------------------------------
  //------------------------  Inner Classes  ---------------------------
  //--------------------------------------------------------------------



  /* This just lets me define it's preferred size method, which was  the
   * only way I could get it to be larger than about a quarter of a 
   * postage stamp's worth.  
   */
  protected class myJPanel extends JPanel {

    protected myJPanel() { super(); }

    @Override
    public Dimension getPreferredSize() {
      return new Dimension(100, 300);  // width x height
    }
  }



  /* A JList to hold the prompts.
   */
  public class myJList extends JList implements PromptsUpdatedListener {

    DefaultListModel prompts;

    public myJList() { 
      super();
    }

    public void initialize() {
      setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
      prompts = new DefaultListModel();
      promptsList.setModel(prompts);
    }

    void populateCharacterSample() {
      prompts.clear();
      prompts.addElement("one");
      prompts.addElement("\u05D0");  // Hebrew
      prompts.addElement("\u05D1");
      prompts.addElement("\u05D2");
      prompts.addElement("two");
    }
    
    // implementation of PromptsUpdatedListener
    @Override
    public void updatePrompts(PromptsUpdatedEvent e) {
      if (debugPrompts)
	System.out.println("Call to updatePrompts");
      String[] promptStrings = e.getCompletionPrompts();
      prompts.clear();
      for (int i=0; i < promptStrings.length; i++) {
	prompts.addElement( promptStrings[i] );
      }
    }

  } // ends myJList


  
  /* The Document/model of the editing component
   */
  public class myDefaultStyledDocument extends DefaultStyledDocument {

    @Override
    public void insertString(int offset, String s, AttributeSet a) {
      if (debugModelAndOutput)
	System.out.println("Document: inserting \"" + s + "\"" + " at " + offset);
      try { 
	super.insertString(offset, s, a);
	if ( s.length() == 1 )
	  textpane.send( makeAddCharacterEvent(s, offset) );
	else
	  if (debugModelAndOutput)
	    System.out.println("Added more than one character -- no event made");
      } catch (BadLocationException e) {
	if (debugModelAndOutput)
	  System.out.println("Can't add here: " + e.offsetRequested());
      }
    }

    @Override
    public void remove(int offset, int length) {
      if (debugModelAndOutput)
	System.out.println("Remove: at " + offset + " length = " + length);
      try {      
	String charsRemoved = getText(offset, length);
	if (debugModelAndOutput)
	  System.out.println("Document: removing " + length + 
			     " characters at " + offset +
			     " \"" + charsRemoved + "\"");
	super.remove(offset, length);
	if ( charsRemoved.length() == 1 )
	  textpane.send( makeDeleteCharacterEvent(offset, charsRemoved) );
	else
	  if (debugModelAndOutput)
	    System.out.println("Removed more than one character -- no event made");
      } catch (BadLocationException ex) {
	if (debugModelAndOutput)
	  System.out.println("Can't remove from here: " + ex.offsetRequested());
      }
    }


    private int oldCursorPosition = 0;

    private ParserInputEvent makeAddCharacterEvent(String character, int positionToTheLeft)
    throws BadLocationException {
      ParserInputEvent e 
	= new ParserInputEvent( textpane,  // source
				character,  // the string that was added
				positionToTheLeft, // position where the insertion occurred
				positionToTheLeft + 1, // new cursor position
				oldCursorPosition,
				true, // really send the change to G2
				ParserInputEvent.ADDED_CHARACTER, // event type
				getText(0, getLength()));    // the entire text
      oldCursorPosition = positionToTheLeft + 1;
      return e;
    }

    private ParserInputEvent makeDeleteCharacterEvent(int offset, String charsRemoved)
    throws BadLocationException {
      ParserInputEvent e 
	= new ParserInputEvent( textpane,  // source
				charsRemoved,  // the character that was deleted
				offset, // position where the insertion occurred
				offset, // new cursor position
				oldCursorPosition,
				true, // really send the change to G2
				ParserInputEvent.DELETED_CHARACTER, // event type
				getText(0, getLength()));    // the entire text
      oldCursorPosition = offset;
      return e;
    }

    

  } // end of myDefaultStyledDocument




  /* The editing pane.
   */
  protected class myJTextPane extends JTextPane 
  implements CaretListener, ListSelectionListener, ParserInputSource, PromptsTarget  {

    protected myJTextPane() { super(); }

    @Override
    public Dimension getPreferredSize() {
      return new Dimension(250, 300);
    }

    private int insertionPoint;
    private Caret c;

    void initialize() {
      c = getCaret();
      c.setDot(0);
      insertionPoint = 0;
    }


    /* N.b. there is no insertString method on a JTextPane. 
     * You have to go via its Document. */


    // implements CaretListener
    @Override
    public void caretUpdate(CaretEvent e) {
      int dot = e.getDot();
      int mark = e.getMark();
      if (debugModelAndOutput)
	System.out.println("CaretEvent at " + getCaretPosition() );
      if ( dot == mark ) {  // no selection
	insertionPoint = dot;
      }
    }


    // implements ListSelectionListener
    @Override
    public void valueChanged(ListSelectionEvent e) {
      if ( e.getValueIsAdjusting() )
	return;
      JList theList = (JList)e.getSource();
      if ( !theList.isSelectionEmpty() ) {
	int index = theList.getSelectedIndex();
	ListModel prompts = theList.getModel();
	String prompt = (String)prompts.getElementAt(index);
	if (debugPrompts)
	  System.out.println("Calling insertPrompt");
	PromptManager.insertPrompt(prompt, this);
	theList.clearSelection();
      }
    }


    // implements ParserInputEventSouroce
    @Override
    public void addParserInputEventListener(ParserInputEventListener l) {
      inputEventListeners.addElement(l);
    }
    @Override
    public void removeParserInputEventListener(ParserInputEventListener l) {
      inputEventListeners.removeElement(l);
    }
    private Vector inputEventListeners = new Vector();



    public void send(ParserInputEvent e) {
      if (debugModelAndOutput)      
	System.out.println("Sending " + e);
      Vector listeners = (Vector)inputEventListeners.clone();
      for (int i=0; i < listeners.size(); i++) {
	ParserInputEventListener listener = (ParserInputEventListener)listeners.elementAt(i);
	switch ( e.getID() ) {
	case ParserInputEvent.CURSOR_CHANGE:
	  listener.cursorPositionChanged(e);
	  break;
	case ParserInputEvent.ADDED_CHARACTER:
	  listener.characterAdded(e);
	  break;
	case ParserInputEvent.DELETED_CHARACTER:
	  listener.characterDeleted(e);
	  break;
	case ParserInputEvent.ADDED_REGION:
	  listener.regionAdded(e);
	  break;
	case ParserInputEvent.DELETED_REGION:
	  listener.regionDeleted(e);
	  break;
	case ParserInputEvent.REPLACED_REGION:
	  listener.regionReplaced(e);
	  break;
	case ParserInputEvent.REPLACED_UNEQUAL_REGIONS:
	  listener.replacedUnEqualRegions(e);
	  break;
	case ParserInputEvent.NO_CHANGE:
	break;
	}
      }
    }


    //---- implementation of PromptsTarget (copied from TextView)

    /* Return the indicated number of characters to the left of the
     * current location of the cursor. If the text is smaller than that
     * number return what there is. */
    @Override
    public String getLeftPromptContext (int length) {
      int here = getCaretPosition();
      if ( here <= length )
	return getText().substring(0, here);
      else {
	return getText().substring(here - length, here);
      }
    }

    /** Return the indicated number of characters to the right of the
     * current location of the cursor. If the text is smaller than that
     * number return what there is. */
    @Override
    public String getRightPromptContext (int length) {
      String text = getText();
      int here = getCaretPosition();
      int textLength = text.length();
      int lengthRemaining = textLength - here;
      if ( lengthRemaining <= length )
	return text.substring(here);
      else 
	return text.substring(here, here + length);
    }


    /** Add the indicated string verbatim to the target text at the current 
     * location of the character-insertion cursor. */
    @Override
    public void insertPromptStringAtCursor (String s) {
      int here = getCaretPosition();
      try {
	getDocument().insertString(here, s, getStyle(styleNames[DEFAULT]));
	if (debugPrompts)
	  System.out.println("Prompt insertion: introduced \"" + s + 
			     "\" at " + here);
      } catch (BadLocationException e) {
	System.err.println("Insertion of " + s + " at " + here + " is out of bounds");
      }
    }

    
    /** Move the location of the character-insertion cusor the indicated
   * number of characters either the right (positive delta) or to the
   * left (negative delta). */
    @Override
    public void moveCursor(int delta) {
      setCaretPosition( getCaretPosition() + delta );
      if (debugPrompts)
	System.out.println("Prompt insertion: move the cursor " + delta +
			   " to " + getCaretPosition());
    }

  } // end of myJTextPane





  //--------------------------------------------------------
  //------------------  Mass Populators  -------------------
  //--------------------------------------------------------

  static final int DEFAULT = 0;
  String[] styleNames = { "default", "bold", "red",
			  "large", "italic", "small" };


  /* Lifted from java.sun.com/docs/books/tutorial/uiswing/components/
   * example-swing/TextComponentDemo.java, then tweaked a little. */
  protected String[] initStyles() {
        //Initialize some styles
        Style def = textpane.addStyle(styleNames[0],
				      textpane.getLogicalStyle());
        StyleConstants.setFontSize(def, 16);
        StyleConstants.setFontFamily(def, "SansSerif");

        Style s = textpane.addStyle(styleNames[1], def);
        StyleConstants.setBold(s, true);

        s = textpane.addStyle(styleNames[2], def);
        StyleConstants.setItalic(s, true);

        s = textpane.addStyle(styleNames[3], def);
        StyleConstants.setFontSize(s, 20);

        s = textpane.addStyle(styleNames[4], def);
        StyleConstants.setFontSize(s, 12);

        s = textpane.addStyle(styleNames[5], def);
        StyleConstants.setForeground(s, Color.red);

        return styleNames;
    }


  String[] testStrings = { "testing ", "\u05D0\u05D1\u05D2", // alef, bet, gimel
			   " two ", "\u6090\u6091\u6092", // random CJK 
  };

  /* Put some stuff into the model, see if it shows up
   * in the view like the example suggests it should. */
  private void populateTheDocument() {
    int cursor = 0;
    int i = 0;
    try {
      for ( i = 0 ; i < testStrings.length; i++) {
	doc.insertString(cursor, 
			 testStrings[i], 
			 textpane.getStyle(styleNames[i]) );
	cursor = cursor + testStrings[i].length();
      }
    } catch (BadLocationException e) {
      System.err.println("Insertion of " + i + " at " + cursor + " is out of bounds");
    }
  }


  /* Also copied from there with virtually no changes.
   */
  private void createActionTable(JTextComponent textComponent) {
    allActions = new Hashtable();
    Action[] actionsArray = textComponent.getActions();
    for (int i = 0; i < actionsArray.length; i++) {
      Action a = actionsArray[i];
      if (listAllAvailableActions)
	System.out.println("Action: " + a);
      allActions.put( a.getValue(Action.NAME), a );
    }
  }
  /* ditto */
  private Action getActionByName(String name) {
    return (Action)allActions.get(name);
  }


  /* ditto */
  protected void addKeymapBindings() {
    // add a new one on top of what's already there
    Keymap keymap = textpane.addKeymap("DDMsBindings",
				       textpane.getKeymap());
    // emacs cntrl-B
    Action action = getActionByName(DefaultEditorKit.backwardAction);
    KeyStroke key = KeyStroke.getKeyStroke( KeyEvent.VK_B, Event.CTRL_MASK );
    keymap.addActionForKeyStroke(key, action);
    // emacs cntrl-F
    action = getActionByName(DefaultEditorKit.forwardAction);
    key = KeyStroke.getKeyStroke( KeyEvent.VK_F, Event.CTRL_MASK );
    keymap.addActionForKeyStroke(key, action);

    textpane.setKeymap(keymap);
  }





  //--------- Connecting, driving from main ----------

  Symbol className = Symbol.intern( "PROCEDURE" );
  Symbol attributeName = Symbol.intern( "TEXT" );

  static TwAccess connection;

  private static TwAccess connect(String host, String port) {
    TwAccess connection = null;  // persnickity compiler
    try { TwGateway.initialize ();
          connection = TwGateway.openConnection(host, port);
    }  catch (Exception e) {
      System.out.println(e);
    }
    if (debugConnection)
      System.out.println("Connected to " + connection);
    return connection;
  }


  private static boolean standalone = false;

  public static void main (String[] args) {
    if ( !standalone ) {
      if ( !( args.length==2 || args.length==3) ) {
	System.out.println("Wrong number of arguments to EditorApp." +
			   "\n  The first argument is the machine to connect to," +
			   "\n  the second is the port number." // +
			   //	 "\n  Optionally, a third argument can be the name of " +
			   //	 "the category to edit."
			   );
	System.exit(-1);
      }
      connection = connect( args[0], args[1] );
    }
    new JEditorTest();
  }


}
