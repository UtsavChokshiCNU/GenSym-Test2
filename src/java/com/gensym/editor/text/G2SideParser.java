/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2SideParser.java
 *
 */
package com.gensym.editor.text;

import java.util.Vector;
import com.gensym.classes.Item;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.ConnectionNotAliveException;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Sorter;
import com.gensym.message.Trace;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.CorruptionException;


/** This is a bridge to the classic parser running on some G2.
 * It accepts ParserInputEvents indicating that it should
 * advance or retreat its analysis relative to the position
 * index and characters supplied by the event. 
 *
 * In response to each event a body of data is returned from
 * the G2 that reflects the new analysis and a set of events
 * are issued: 
 *
 * ParsingStatusUpdated - is the text acceptable according to
 *   the G2 grammar and if not, what the problem is.
 * PromptsUpdated -  an object that packages the prompts for
 *   follow on tokens or categories given the current position.
 * TextCompleteStatus - whether or not the text as it stands
 *   could be concluded as a new value of the attribute being
 *   edited.
 * TokenData - indicies indicating where the token to the
 *   immediate left of the current position begins and ends,
 *   whether it is complete, and its index in the parsing
 *   context. 
 *
 * @author David McDonald
 * @version 1.0
 * @undocumented -- final Text Editor API is still under review
 */

public class G2SideParser  implements ParserInputEventListener {

  private boolean debug = false;
  private boolean debugPrompts = false;
  public void setDebug(boolean b) { debug = b; }

  int transmitionTimeTimeout = 10000; // in milliseconds, i.e. 10 seconds
  /* Add in a delta based on how much computing happens on the g2 side.
   * Note that all this is a gross guestimate. */
  int newContextTimeout   = transmitionTimeTimeout + 1000;
  int clearContextTimeout = transmitionTimeTimeout + 1000;
  int concludeTimeout     = transmitionTimeTimeout + 10000;
  int updateTimeout       = transmitionTimeTimeout + 5000;
  int ceateParsingContextTimeout = 5000;   // in milliseconds

  // Given what's commented out, this function has no utility over just
  // using the initial values. But it's a placeholder until I can find
  // something like this that does work.
  void initializeTimeouts() {  //long defaultFromContext) {
    transmitionTimeTimeout = 2000000; //(int)defaultFromContext;
    newContextTimeout   = transmitionTimeTimeout + 1000;
    clearContextTimeout = transmitionTimeTimeout + 1000;
    concludeTimeout     = transmitionTimeTimeout + 10000;
    updateTimeout       = transmitionTimeTimeout + 5000;
  }


  private TwAccess connection;
  void setConnection(TwAccess a) { connection = a; }
  TwAccess getConnection() { return connection; }

  private Session session;
  void setSession(Session s) { session = s; }


  private Integer parsingContext = theNullParsingContext();
  /** Returns the handle to the structure used by G2 to represent
   * this session. */
  Integer getParsingContext() { return parsingContext; }
  /* A setter makes no sense since this is the object that opens the
   * connection to a parsing context on the G2 side. */

  private Item item;
  private Symbol nameOfSlotBeingEdited;
  private Symbol categoryName;

  private ParserInputEvent inputEvent;

  void setInputEvent(ParserInputEvent e) { inputEvent = e; }
  private void initializeInputEvent() {   // NO_CHANGE
    inputEvent = new ParserInputEvent( (ParserInputSource)session.getEditor() );
  }


  void removeBackPointers() {
    connection = null;
    session = null;
    inputEvent = null;
  }

  private String[] initialCategoryPrompts;
  private String[] initialCompletionPrompts;

  /** Issues a PromptsUpdateEvent providing the prompts that hold at
   * position zero in a text of the category being parsed. */
  public void issueInitialPrompts() {
    distributePromptSet
      ( new PromptsUpdatedEvent( this, inputEvent,
				 completionChoices,
				 categoryChoices) );
  }



  //---------------- Constructors --------------------------

  public G2SideParser() {}

  /** Creates a new parsing context for the grammar category appropriate
   * to the class and attribute. 
   *
   * This is the constructor that is used in concert with the
   * menu-initiated Session constructor. 
   *
   * @param connection  This is the TwAccess that defines what G2 we
   * are connecting to.
   * @param session  A backpointer to the Session object that is 
   * coordinating this instance of text editing. It is included in
   * some of the events that the parser issues to provide a 'source'
   * in the case where there are multiple sessions and the listeners
   * have to be careful about what they listen to.
   * @param className  The name of the class that owns the attributue
   *   to be edited, given as a symbol.
   * @param attributeName  A symbol naming the attribute to be edited.
  * @undocumented -- final Text Editor API is still under review
   */
  public G2SideParser( TwAccess connection, Session session,
		       Symbol className, Symbol attributeName ) {
    initializationsForStandardSetup(connection, session, className, attributeName);
  }

  void initializationsForStandardSetup( TwAccess connection, Session session,
					Symbol className, Symbol attributeName ) {
    this.connection = connection;
    this.session = session;
    initializeTimeouts(); // connection.getDefaultCommunicationTimeOut() );
    initializeInputEvent();
    getParsingContext(className, attributeName);
    ongoingStatus = true;  // Status starts out Ok. Change this when there's
                           // initial text.
  }

  
  /** This constructor is used when you are just using the parser to vet
   * the text given some governing grammatical category.
   *
   * @param connection  This is the TwAccess that defines what G2 we
   *   are connecting to.
   * @param session  A backpointer to the Session object that is 
   *   coordinating this instance of text editing. It is included in
   *   some of the events that the parser issues to provide a 'source'
   *   in the case where there are multiple sessions and the listeners
   *   have to be careful about what they listen to.
   * @param categoryName  A symbol naming a category in the G2 grammar.
   *   If there is no such category the attempt to create the parsing
   *   context will fail.
  * @undocumented -- final Text Editor API is still under review
   */
  public G2SideParser(TwAccess connection, Session session, 
		      Symbol categoryName) {
    this.connection = connection;
    this.session = session;
    this.categoryName = categoryName;
    initializeTimeouts();
    initializeInputEvent();
    getParsingContextForCategory(categoryName);
    ongoingStatus = true;
  }


  /** This constructor is used when doing tests that make direct calls
   * to the primitive methods in this class, i.e. not using ParserInputEvents.
   * @param connection  This is the TwAccess that defines what G2 we
   *   are connecting to.
   * @param categoryName  A symbol naming a category in the G2 grammar.
   *   If there is no such category the attempt to create the parsing
   *   context will fail. This can be checked by calling setupWasSuccessful().
   */
  public G2SideParser(TwAccess connection, Symbol categoryName) {
    this.connection = connection;
    this.categoryName = categoryName;
    initializeTimeouts();
    initializeInputEvent();
    getParsingContextForCategory(categoryName);
    ongoingStatus = true;
  }



  /** Provides a representation of the G2 that is doing the parsing
   * and the handle of the active parsing context on that G2.
  * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public String toString() {
    String s = super.toString();
    s += "Parsing context #" + parsingContext;
    if ( connection != null )
       s += " " + connection.toString();
    return s;
  }





  //------------- managing the Parsing Context --------------------

  private Integer theNullParsingContext() {
    return -1;
  }

  /** This predicate reports whether or not it was possible to establish
   * an editing context on the G2 we are connected to.  If there is no
   * context there can be no editing and the session should be aborted.
  * @undocumented -- final Text Editor API is still under review
   */
  boolean setupWasSuccessful() {
    if ( parsingContext.intValue() == -1 )
      return false;
    else
      return true;
  }

   
  /* getParsingContext is called as part of initializing the an instance
   * of the parser. It establishes a parsing-context object on the G2-side
   * of the fence. The rpc returns a handle (and Integer) representing 
   * that context which it expects to see on each subsequent rpc as the
   * way of keeping simultaneous editing sessions distinct.  The handle
   * is extracted from the rpc's return value by a call to unpackParsing-
   * ContextReturnStructure, which side-effect's the local boolean that is
   * used to record whether a successful setup occurred.
   */
  private void getParsingContext(Symbol className, Symbol attributeName)  {
    Object[] args = new Object[5];
    args[0] = theNonSymbolValue; // for the grammar category
    args[1] = className;
    args[2] = attributeName;
    args[3] = theNonSymbolValue; // for the slot-component-name
    args[4] = theNonSymbolValue; // for the slot-component-indicator

    Object returnValue = null;
    try { 
    	returnValue  = connection.callRPC( _createParsingContext, args,
					     newContextTimeout);
    } catch (ConnectionNotAliveException e) {
      session.rugPulledOutFromUnder(e);
    } catch (G2AccessException e) {
      e.printStackTrace();
      return;
    }
    if (returnValue instanceof Boolean) {
      // This takes the shortcut of knowning that the only situation in
      // which the rpc will return a boolean is if it couldn't create
      // the context.  The reason is because it can't find a grammar category
      // to parse to.
      //  This is a log message, but how to set those up I couldn't sus out.
      if (debug)
	System.out.println("DDM:  g2-api-create-parsing-context returned false");
    } else {
      if (returnValue instanceof Structure) {
	unpackParsingContextReturnStructure( (Structure)returnValue );
      } else {  // ditto
	if (debug)
	  System.out.println("DDM:  Unexpected return value from getParsingContext");
      }
    }
  }

  private void getParsingContextForCategory( Symbol categoryName) {
    Object[] args = new Object[5];
    args[0] = categoryName;
    args[1] = theNonSymbolValue;
    args[2] = theNonSymbolValue;
    args[3] = theNonSymbolValue;
    args[4] = theNonSymbolValue;
    
    Object returnValue = null;
    try { 
    	returnValue = connection.callRPC( _createParsingContext, args, 
					    newContextTimeout);
    } catch (ConnectionNotAliveException e) {
      session.rugPulledOutFromUnder(e);
    } catch (G2AccessException e) {
      e.printStackTrace();
      return;
    }
    if (returnValue instanceof Boolean) {
      if (debug)
	System.out.println("DDM:  g2-api-create-parsing-context returned false");
    } else {
      if (returnValue instanceof Structure) {
	unpackParsingContextReturnStructure( (Structure)returnValue );
      } else {
	if (debug)
	  System.out.println("DDM:  Unexpected return value from getParsingContext");
      }
    }
  }



  //---- Clear ----------

  /** As its name suggests, this method will reset the G2-side parsing context
   * to the state it was in when the context was initialized, i.e. when there
   * was no text under analysis.  After doing the reinitialization, it sends
   * a PromptsUpdatedEvent with the PromptSet that is appropriate to the
   * beginning of an Editing Session when the cursor is positioned at the
   * index zero.  It is the responsibility of other objects to ensure that
   * the text in view is also cleared.
  * @undocumented -- final Text Editor API is still under review
   */
  public void clearParsingContext() {
    Object[] args = new Object[1];
    args[0] = parsingContext;
    Boolean returnValue = null;
    try { 
    	returnValue = (Boolean)connection.callRPC( _clearParsingContext, args,
						     clearContextTimeout);
    } catch (ConnectionNotAliveException e) {
      session.rugPulledOutFromUnder(e);
    } catch (G2AccessException gae) {
      if (debug)
	System.out.println("AccessError while clearing G2-side parsing-context:\n  "
                           + gae);
      // convert that into a log. 
    }
    // reset the prompts to be what they were at the start
    issueInitialPrompts();

    distributeParsingStatusUpdates
      ( new ParsingStatusUpdatedEvent(this, session, true) );
  }



  //---- Shutdown -------

  /** This method will send the appropriate signal to the G2-side parser
   * so that it will terminate and clean up its parsing state properly.
  * @undocumented -- final Text Editor API is still under review
   */
  public void shutdownParsingContext() {
    Object[] args = new Object[1];
    args[0] = parsingContext;
    Boolean returnValue = null;
    try { 
    	returnValue = (Boolean)connection.callRPC( _deleteParsingContext, args,
						     clearContextTimeout);
    } catch (ConnectionNotAliveException e) {
      session.rugPulledOutFromUnder(e);
    } catch (G2AccessException gae) {
      if (debug)
	System.out.println("AccessError while deleting G2-side parsing-context:\n  "
			    + gae);
      // convert that into a log. 
    }
    //The session is being shut down, but for potential reused editors, 
    //we need to tell it that everything's in good order, in case the
    //old editor had a bad status.
    distributeParsingStatusUpdates
      ( new ParsingStatusUpdatedEvent(this, session, true) );
  }



  //---- Conclude

  /** The parsing context contains the analysis of a particular text as
   * the attribute of a particular class or as a particular grammar category.
   * This method will attempt to conclude that text as the attribute of
   * the indicated item. 
   *
   * @return If the conclude went through successfully then the value of
   *  this method is true. If the compiler found a problem with the text
   *  then a StatusChangeEvent will be issued indicating the problem
   *  and this will return false. Any other problem with the context will
   *  also have this return false. 
   *
   * @param item  The item with the attribute where the new text is to be
   *   concluded. 
   * @param editingForRuntimeChange  Indicates whether the conclude should
   *   permanently affect the KB (FALSE) or it should be revertable (TRUE). 
  * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public boolean attemptToConcludeParsingContext (Item item, 
						  Boolean editingForRuntimeChange) {
    itemBeingConcluded = item;
    editingForRuntimeChangeP = editingForRuntimeChange;

    Object[] args = new Object[3];
    args[0] = parsingContext;
    args[1] = item;
    args[2] = editingForRuntimeChange;
    
    Object returnValue = null;
    try { 
    	returnValue = connection.callRPC(_commitParseResult, args,
					   concludeTimeout);
    } catch (ConnectionNotAliveException e) {
      session.rugPulledOutFromUnder(e);
    } catch (G2AccessException e) {
      Trace.exception(e, "Problem calling _commitParseResult");
      if (debug)
	System.out.println("DDM: problem calling _commitParseResult");
      return false;
    }
    boolean noProblems = unpackConcludeReturnStructure( (Structure)returnValue );
    if ( noProblems )
      return true;
    else
      return false;
  }



   


  //------------ Cursor Movement -------------------

  /* This is used with advances and retreats to ensure that the
   * parser is correctly updated if what appeared to be a simple
   * addition or deletion was actually a replacement and the
   * parser should retreat back over some part of the text. */
  int lastCursorPositionSentToG2 = 0;


  /** This sends the G2-side parser the information it needs to reposition its
   * internal position index so that any subsequent additions or deletions will
   * now be relative to that position.  The usual set of events are triggered
   * just as with the addition or deletion of text. The prompts and status
   * information that are generated by this transaction are relative to the
   * indicated cursor position.
  * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public void cursorPositionChanged (ParserInputEvent e) {
    setInputEvent(e);
    adjustCursorPosition( e.getCursor(), e.getText() );
  }

  /* Does the actual transaction with G2. This is the constant part that
   * could run with any number of different setups depending on the
   * interface involved.
   */
  
  private void adjustCursorPosition(int newPosition, String theText) {
    Object[] args = { parsingContext, newPosition, theText };
    lastCursorPositionSentToG2 = newPosition;
    if (debug)
      System.out.println("DDM: telling G2 to reposition the cursor to " + newPosition +
			 "\n    on the text \"" + theText + "\"");
    Object returnValue = null;
    try { 
    	returnValue = connection.callRPC( _shiftCursorPosition, args,
					    updateTimeout);
    } catch (ConnectionNotAliveException e) {
      session.rugPulledOutFromUnder(e);
    } catch (G2AccessException ae) {
      // make an announcement
      ae.printStackTrace();
      return;
      // If this doesn't work, then the real 'fix' is to disallow the editing
      // action. In effect, undo it.  That will require some machinery, so putting
      // it off.
    }
    if (returnValue instanceof Structure) {
      unpackParseUpdateReturnStructure( (Structure)returnValue );
    } else {
      // If we get here, it's a coding bug on the G2 side. What to do?
    }
  }


  //---------- Adding/deleting character/regions --------


  String lastTextSentToG2 = "";


  /** Passes the character and the position at which it is to be added
   * to the parser in the G2 of the ongoing parsing context and issues
   * the standard set of events that reflect the change in the parser's
   * analysis, i.e. PromptsUpdated, ParsingStatusUpdated, TextCompleteStatus,
   * and TokenData.
  * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public void characterAdded (ParserInputEvent e) {
    setInputEvent(e);
    retreatFirstIfNecessary(e);
    updateParseAnalysis( e.getText(), e.getCursor(), true);
  }

  /** Given that the current implementation of the editor->parser protocol
   * groups set of otherwise individuated events into sets of composite
   * events as dictated by a timer, it is entirely possible for one net
   * ParserInputEvent to include both a cursor movement and a change
   * to the content of the text. This method detects that by looking
   * at the old and new position of the cursor. 
   */
  // This check is especially important because such an 'invisible' retreat
  // can lead to the G2 side thinking that it's model of its indicies
  // are invalid and reparsing the entire text from the beginning to be
  // sure that it's in sync.  Logically it's possible to also need an
  // advanceAfterwardsIfNecessary, but I'm holding off on that for the
  // moment until I've set up a reasonable size automatic regression test.
  void retreatFirstIfNecessary(ParserInputEvent e) {
    if ( e.getOldCursor() > e.getCursor() ) {
      if (debug)
	System.out.println("embedded retreat from position " + e.getOldCursor());
      updateParseAnalysis(e.getText(), e.getCursor(), false);
    }
  }


  /** Passes to the parser in the G2 of the ongoing parsing context the
   * information that it should delete a character at the indicated
   * position and issues the standard set of events. 
  * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public void characterDeleted (ParserInputEvent e) {
    setInputEvent(e);
    updateParseAnalysis( e.getText(), e.getCursor(), false);
  }


  /** Passes the indicated characters and the position at which they
   * are to be added to the parser in the G2 of the ongoing parsing
   * context and issues the standard set of events that reflect the
   * change in the parser's analysis, i.e. PromptsUpdated,
   * ParsingStatusUpdated, TextCompleteStatus, and TokenData.  
   * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public void regionAdded (ParserInputEvent e) {
    /* we know this addition will translate to G2 as advance to
     * the position of the cursor, so we use the setup that's
     * already in hand rather than copy it. */ 
    characterAdded(e);
  }
  

  /** Passes to the parser in the G2 of the ongoing parsing context the
   * information that it should delete the characters between the
   * indicated indicies and issues the standard set of events. 
   * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public void regionDeleted (ParserInputEvent e) {
    /* see regionAdded */
    characterDeleted(e);
  }


  /** A replacement is interpreted as a retreat followed by an
   * advance, optionally followed by a cursor movement if the
   * cursor is not at the end of the advance in the event being
   * decoded. 
   * @undocumented -- final Text Editor API is still under review
   */
  /* ...which is frighteningly inefficient given that each of those
   * is a separate rpc given our present interface into g2. But
   * right now (4/14/98) it's unclear whether it's worth the programming
   * to add another rpc that would do all this on the g2 side. */
  @Override
  public void regionReplaced(ParserInputEvent e) {
    setInputEvent(e);
    String theText = e.getText();
    updateParseAnalysis(theText, e.getRegionStart(), false);
    updateParseAnalysis(theText, e.getRegionEnd(), true);
    if ( e.getRegionEnd() != e.getCursor() )
      adjustCursorPosition(e.getCursor(), theText);
  }


  /** The replacement of unequal regions of texts is also an retreat
   * followed by an advance and an optional cursor movement, but
   * we have to be careful about which positions we use, those of the
   * new, replacing, region or of the old region that was replaced.
   */
  @Override
  public void replacedUnEqualRegions(ParserInputEvent e) {
    setInputEvent(e);
    String theText = e.getText();
    updateParseAnalysis(theText, e.getOldStartPosition(), false);
    updateParseAnalysis(theText, e.getNewEndPosition(), true);
    if ( e.getNewEndPosition() != e.getCursor() )
      adjustCursorPosition(e.getCursor(), theText);
  }


  /** This is the common final path by which changes are passed to 
   * the G2-side parser.  The G2 Parsing API construes all text change 
   * operations as either advances or retreats to an indicated 
   * position given the text that it is passed in.
   */
  public void updateParseAnalysis (String theWholeText, int cursorPosition, 
				    boolean advancing) {

    updateParseAnalysis(theWholeText, cursorPosition, advancing, true);
  }

  private void updateParseAnalysis (String theWholeText, int cursorPosition, 
				    boolean advancing, boolean reportResult) {
    lastCursorPositionSentToG2 = cursorPosition;
    lastTextSentToG2 = theWholeText;

    Object[] args = new Object[4];

    args[0] = parsingContext;

    if ( !advancing )  // i.e. we're retreating
      args[1] = cursorPosition ;
    else 
      args[1] = theNonFixnumValue;

    if ( advancing )
      args[2] = cursorPosition;
    else 
      args[2] = theNonFixnumValue;

    args[3] = theWholeText;

    if (debug)
      if (advancing)
	System.out.println("DDM: sending G2: text = \"" + args[3] + "\"" +
			   "\n    advance = " + args[2] );
      else
	System.out.println("DDM: sending G2: text = \"" + args[3] + "\"" +
			   "\n    retreat = " + args[1] );

    Object returnValue = null;
    try { 
    	returnValue = connection.callRPC( _updateParsingContext, args,
					    updateTimeout);
    } catch (ConnectionNotAliveException e) {
      session.rugPulledOutFromUnder(e);
    } catch (G2AccessException ae) {
      if (debug)
	System.out.println("DDM: Problem updating Parsing Context:" + 
			   "\n  backupIndex = " + args[1] +
			   "\n  advanceIndex = " + args[2] +
			   "\n  text = " + args[3] +
			   "\n  parsingContext = " + args[0] +
			   "\n\nThe G2AccessException is:\n  " + ae );
      ae.printStackTrace();
      // Announce that there was a problem. Find out from Mike/Vikram what
      // sorts of things can cause this exception and how one finds out
      // which it was in a given instance.
      return;
    }
    if (reportResult) {
      if (returnValue instanceof Boolean) {
	if (debug)
	  System.out.println("DDM: Update: Parsing context missing on G2 side");
	// throw something, but what?
      } else
	if (returnValue instanceof Structure) {
	  unpackParseUpdateReturnStructure( (Structure)returnValue );
	} else {
	  if (debug)
	    System.out.println("DDM: Unexpected return value from updateParsingContext");
	  // is this fatal?  It would amount to a coding bug.  But if it could happen
	  // stocastically for other reasons involved with the mechanisms of the
	  // JavaLink interface or something, then it should signal.
	}
    }
  }




  //------ RPCs to the G2-side parser -------------

  static Symbol _updateParsingContext
                   = Symbol.intern("G2-UPDATE-PARSING-CONTEXT");
  static Symbol _createParsingContext
                   = Symbol.intern("G2-CREATE-PARSING-CONTEXT");
  static Symbol _createParsingContextJustForCategory
                   = Symbol.intern("G2-CREATE-PARSING-CONTEXT-JUST-FOR-CATEGORY");
  static Symbol _createParsingContextForItemAndSlot
                   = Symbol.intern("G2-CREATE-PARSING-CONTEXT-FOR-ITEM-AND-SLOT");
  static Symbol _commitParseResult
                   = Symbol.intern("G2-COMMIT-PARSE-RESULT");
  static Symbol _deleteParsingContext
                   = Symbol.intern("G2-DELETE-PARSING-CONTEXT");
  static Symbol _clearParsingContext
                   = Symbol.intern("G2-CLEAR-PARSING-CONTEXT");
  static Symbol _shiftCursorPosition
                   = Symbol.intern("G2-SHIFT-CURSOR-POSITION");


  private String theNonFixnumValue = "not a fixnum";
  // In this API, the G2-side will do a type-check against an index
  // parameter and set it to nil (on the Lisp-side) if it isn't a fixnum.
  // Since we can't pass the eqivalent of Nil over javalink, this provides
  // an emulation. 

  private Integer theNonSymbolValue = 0;
  // This is used when the G2-side would want a nil but won't be allowed
  // to get one because null's aren't acceptable to the interface.
  // The G2-side code has checks against these arguments, and if they
  // aren't of the expected data types sets them to nil.








  //
  // ----------- Unloading the return value from the Parser on the G2-side ----
  //

  static Symbol _parsingContextHandle
                   = Symbol.intern("PARSING-CONTEXT-HANDLE");
  static Symbol _ok
                   = Symbol.intern("OK");
  static Symbol _endableP
                   = Symbol.intern("ENDABLE-P");
  static Symbol _description
                   = Symbol.intern("DESCRIPTION");
  static Symbol _errorIndex
                   = Symbol.intern("ERROR-INDEX");
  static Symbol _longestCommonCompletion
                   = Symbol.intern("LONGEST-COMMON-COMPLETION");
  static Symbol _categoryChoices
                   = Symbol.intern("CATEGORY-CHOICES");
  static Symbol _completionChoices
                   = Symbol.intern("COMPLETION-CHOICES");
  static Symbol _tokenCompleteP
                   = Symbol.intern("TOKEN-COMPLETE-P");
  static Symbol _tokenData
                   = Symbol.intern("TOKEN-DATA");


  /* This is a one-off unpacker that is run as part of the intializations.
   * It extracts the parsing context handle and the initial prompts from
   * the return value, and updates the 'we have started' state information
   * with a call to setupWasSuccessful(). It also stashes away the category
   * and completion promts that were returned so that they can be provided
   * later should we clear the text and return to this initial state.
   */
  private void unpackParsingContextReturnStructure(Structure ret) {
    unpackPromptInformation(ret);
    initialCompletionPrompts = completionChoices;
    initialCategoryPrompts = categoryChoices;

    unpackCompletionInformation(ret);

    try { 
    	parsingContext = (Integer)ret.getAttributeValue(_parsingContextHandle); }
    catch (NoSuchAttributeException e) {
      parsingContext = theNullParsingContext();
      throw new CorruptionException(e, "Problem creating server-side parsing context");
    }
    if ( setupWasSuccessful() ) {
      // also a log msg
      if (debug)
	System.out.println("DDM:  Got a parsing context: " + parsingContext);
    }
    else
      if (debug)
	System.out.println("DDM: unsuccessful parsing context, " + parsingContext
			   + ", returned from G2");
  }



  private void unpackParseUpdateReturnStructure(Structure ret) {
    //System.out.println( ret );  
    if (unpackErrorInformation(ret)) {  // see hack #2
      unpackPromptInformation(ret);
      unpackStatusInformation(ret);
      unpackCompletionInformation(ret);
      unpackTokenCompletenessInformation(ret);
    }
  }


  //--------  Prompt Information --------------

  Object longestCommonCompletionOrFalse;
  Sequence rawCategoryChoices;
  Sequence rawCompletionChoices;
  String[] latestCategoryChoices;
  String[] latestCompletionChoices;
  String[] categoryChoices = { "" };
  String[] completionChoices = { "" };


  private void unpackPromptInformation(Structure ret) {
    try {
      longestCommonCompletionOrFalse = ret.getAttributeValue(_longestCommonCompletion);
      rawCategoryChoices = (Sequence)ret.getAttributeValue(_categoryChoices);
      rawCompletionChoices = (Sequence)ret.getAttributeValue(_completionChoices);
    } catch (NoSuchAttributeException e) {
      throw new CorruptionException(e, "Problem unpacking prompting information");
    }
    latestCategoryChoices = canonicalizePrompts(rawCategoryChoices);
    latestCompletionChoices = canonicalizePrompts(rawCompletionChoices);
    if ( newSetOfPrompts(latestCompletionChoices, completionChoices) ) {
      completionChoices = latestCompletionChoices;
      categoryChoices = latestCategoryChoices;
      distributePromptSet
	( new PromptsUpdatedEvent( this, inputEvent,
				   completionChoices,
				   categoryChoices) );
    }
  }


  private Vector promptsListeners = new Vector();

  public void addPromptsUpdatedListener(PromptsUpdatedListener l) {
    promptsListeners.addElement(l);
  }

  public void removePromptsUpdatedListener(PromptsUpdatedListener l) {
    promptsListeners.removeElement(l);
  }

  private void distributePromptSet(PromptsUpdatedEvent e) {
    //System.out.println("Distributing prompts");
    Vector list = (Vector)promptsListeners.clone();  // probably unnecessary
    for ( int i = 0; i < list.size(); i++ ) {
      PromptsUpdatedListener listener = (PromptsUpdatedListener)list.elementAt(i);
      //System.out.println("Listener = " + listener);
      listener.updatePrompts(e);
    }
  }


  private String[] canonicalizePrompts(Sequence promptSequence) {
    String[] canonicalPrompts = copyToStringArray(promptSequence.getContents());
    Sorter.sort(canonicalPrompts, Sorter.ASCENDING);
    return canonicalPrompts;
  }

  boolean newSetOfPrompts(String[] incomingPrompts, String[] prompts) {
    if (debugPrompts) {
      System.out.println(prompts.length + " Existing prompts: ");
      for (int i=0; i<prompts.length; i++) {
	System.out.println(i + ". \"" + prompts[i] + "\"");
      }
      System.out.println(incomingPrompts.length + " incoming: ");
      for (int i=0; i<incomingPrompts.length; i++) {
	System.out.println(i + ". \"" + incomingPrompts[i] + "\"");
      }
    }
    if ( incomingPrompts.length != prompts.length )
      return true;
    for (int i=0; i<prompts.length; i++) {
      if (!incomingPrompts[i].equals(prompts[i]))
	return true;
    }
    return false;
  }

  private String[] copyToStringArray( Object[] a) {
    String[] s = new String[ a.length ];
    for (int i = 0; i < a.length; i++) {
      s[i] = (String)a[i];
    }
    return s;
  }



  //--------- Status of the Parse Information --------

  boolean ongoingStatus;
  Boolean status;
  Object errorTextOrFalse;
  String errorText;
  Object errorIndexOrFalse;
  int errorIndex;

  private void unpackStatusInformation(Structure ret) {
    try {  
      status = (Boolean)ret.getAttributeValue(_ok);
    } catch (NoSuchAttributeException e) {
      throw new CorruptionException(e, "Problem unpacking status information");
    }

    boolean newStatus = status.booleanValue();

    ParsingStatusUpdatedEvent updateEvent;

    if ( newStatus != ongoingStatus ) {
      if ( newStatus )
	updateEvent = new ParsingStatusUpdatedEvent(this, session, true);
      else {
	updateEvent = new ParsingStatusUpdatedEvent
	  (this, session, false, errorIndex, errorText);
      }
      distributeParsingStatusUpdates( updateEvent );
      ongoingStatus = newStatus;
    }
    else 
      if ( ! newStatus ) {
	// Even though the status hasn't changed, we should send off an 
	// update because it's likely that the index of the site in
	// the text where it went bad has changed and the text viewer
	// will want to update its error designator accordingly.
	updateEvent = new ParsingStatusUpdatedEvent
	  (this, session, false, errorIndex, errorText);
	distributeParsingStatusUpdates( updateEvent );
      }
  }



  /* In the service of hack #2 that gets around spurious bugs in retreats into
   * strings, unpackErrorInformation returns true in most cases, but returns
   * false when this hack applies, with the effect of canceling the unpacking
   * of the rest of the return information that was currently underway. */ 

  private boolean unpackErrorInformation(Structure ret) {
    try { 
    	status = (Boolean)ret.getAttributeValue(_ok);
    } catch (NoSuchAttributeException e) {
      throw new CorruptionException(e, "Return value is missing 'ok' information:1");
    }
    if ( status.booleanValue() ) // i.e. there was nothing wrong, the parse was good
      return true;
    else {
      /* process the location of the error */
      try { 
    	  errorIndexOrFalse = ret.getAttributeValue(_errorIndex);
      } catch (NoSuchAttributeException e) {
	throw new CorruptionException(e, "Return value is missing its errorIndex");
      }
      if (errorIndexOrFalse instanceof Boolean)
	errorIndex = -1;
      else {
	Integer temp = (Integer)errorIndexOrFalse;
	errorIndex = temp.intValue();
	}

      /* process the description */
      try { 
    	  errorTextOrFalse = ret.getAttributeValue(_description);
      } catch (NoSuchAttributeException e) {
	throw new CorruptionException(e, "Return value is missing its description");
      }
    
      if (errorTextOrFalse instanceof String)	
    	  errorText = (String)errorTextOrFalse;
      else // it's now undefined as far as what we've programmed goes
    	  errorText = "";
    
      /* Check for hack #2 */
      if ( !retreatHackUnderway
	   && ( errorIsInsideAString(errorIndex, session.getText()) )) {
 	if (debug)
	  System.out.println("It thinks the hack applies" +
			     "\nThe position of the error is " + errorIndex +
			     "\nThe position of the last quote is " +
			     posOfLastQuotesBeforeErrorIndex +
			     "\nThe position of the trailing quote is " +
			     posOfQuoteAfterErrorIndex );
	applyErrorInsideAStringHack();
	return false; // the rest of the return processing of this call is moot
      }

      return true;
    }
  }




  private Vector statusListeners = new Vector();

  public void addParsingStatusUpdatedListener(ParsingStatusUpdatedListener l) {
    statusListeners.addElement(l);
  }

  public void removeParsingStatusUpdatedListener(ParsingStatusUpdatedListener l) {
    statusListeners.removeElement(l);
  }

  private void distributeParsingStatusUpdates(ParsingStatusUpdatedEvent e) {
    Vector list = (Vector)statusListeners.clone();
    // given this design, nobody is going to be adding listeners while this event
    // goes out, on the other hand, consistency with the general design is probably
    // a good thing. (or is this just a awt convention ?)

    for ( int i = 0; i < list.size(); i++ ) {
      ParsingStatusUpdatedListener listener = 
	(ParsingStatusUpdatedListener)list.elementAt(i);
      listener.changeParsingStatus(e);
    }
  }





  //--------- Completion Information -------

  boolean endableP;

  boolean initiallyComplete;
  boolean hasBeenComplete;
  boolean hasBeenIncomplete;

  private boolean unpackCompletionInformation(Structure ret) {
    // Do a special check for the endable-p key since it will definitively not
    // be present in 5.0r1 G2's, only in 5.0r2 or post rev.1 development G2s.
    Boolean returnedValue = Boolean.FALSE;
    try { 
    	returnedValue = (Boolean)ret.getAttributeValue(_endableP); }
    catch (NoSuchAttributeException e) {
      // Send out a log message?  Where?
    }
    endableP = returnedValue.booleanValue();
    boolean sendCompleteEvent = false;

    if ( endableP ) {
      if ( hasBeenIncomplete || !initiallyComplete ) {
	hasBeenComplete =  true;
	sendCompleteEvent = true;
      }
    } 
    else {
      if ( hasBeenComplete ) {
	hasBeenIncomplete = true;
	sendCompleteEvent = true;
      }
    }

    if ( sendCompleteEvent ) {
      distributeTextCompleteStatus
	( new TextCompleteStatusEvent(this, session, endableP) );
    }
    return( endableP );
  }



  private Vector textCompleteListeners = new Vector();

  /**
  * @undocumented -- final Text Editor API is still under review
  */
  public void addTextCompleteStatusListener(TextCompleteStatusListener l) {
    textCompleteListeners.addElement(l);
  }

  /**
  * @undocumented -- final Text Editor API is still under review
  */
  public void removeTextCompleteStatusListener(TextCompleteStatusListener l) {
    textCompleteListeners.removeElement(l);
  }

  private void distributeTextCompleteStatus(TextCompleteStatusEvent e) {
    Vector list = (Vector)textCompleteListeners.clone();
    for ( int  i = 0; i < list.size(); i++ ) {
      TextCompleteStatusListener listener =
	(TextCompleteStatusListener)list.elementAt(i);
      listener.checkStatus(e);
    }
  }




    //-------- Information about the token under analysis ------

  private boolean currentTokenIsComplete;
  private Integer indexOfCurrentToken;
  private Integer startPositionOfCurrentToken;
  private Integer endPositionOfCurrentToken;

  private void unpackTokenCompletenessInformation(Structure ret) {
    // This attribute is also not part of G2 5.0r1
    Boolean returnedValue = Boolean.FALSE;
    try { 
    	returnedValue = (Boolean)ret.getAttributeValue(_tokenCompleteP); }
    catch (NoSuchAttributeException e) { 
      return; 
    }
    currentTokenIsComplete = returnedValue.booleanValue();

    Sequence data = null;
    try { 
    	data = (Sequence)ret.getAttributeValue(_tokenData); }
    catch (NoSuchAttributeException e) { 
      return;
    }
    indexOfCurrentToken = (Integer)data.elementAt(0);
    startPositionOfCurrentToken = (Integer)data.elementAt(1);
    endPositionOfCurrentToken = (Integer)data.elementAt(2);

    distributeTokenData( new TokenDataEvent(this, currentTokenIsComplete,
					    indexOfCurrentToken.intValue(),
					    startPositionOfCurrentToken.intValue(),
					    endPositionOfCurrentToken.intValue()) );
  }


  private Vector tokenDataListeners = new Vector();

  /**
  * @undocumented -- final Text Editor API is still under review
  */
  public void addTokenDataListener(TokenDataListener l) {
    tokenDataListeners.addElement(l);
  }

  /**
  * @undocumented -- final Text Editor API is still under review
  */
  public void removeTokenDataListener(TokenDataListener l) {
    tokenDataListeners.removeElement(l);
  }

  private void distributeTokenData(TokenDataEvent e) {
    Vector list =  (Vector)tokenDataListeners.clone();
    for (int i = 0; i < list.size(); i++ ) {
      TokenDataListener listener = (TokenDataListener)list.elementAt(i);
      listener.assimilateTokenData(e);
    }
  }


  //---------- Conclude Information ------------

  private boolean unpackConcludeReturnStructure(Structure ret) {
    Boolean didItWork;
    try { 
    	didItWork = (Boolean)ret.getAttributeValue(_ok);
    } catch (NoSuchAttributeException e) {
      throw new CorruptionException(e, "Return value is missing 'ok' information:2");
    }
    if ( didItWork.booleanValue() ) {
      return true;
    }
    else {
      unpackErrorInformation(ret);

      // See 'hack #1' below
      if (   ( errorIndex == -1 )
	  && ( errorText.equalsIgnoreCase(INCOMPLETE_PARSE))
          && !alreadyTriedAddingFinalSpace  ) {

	if (debug) 
	  System.out.println("Conclude returned 'incomplete parse', " +
			     "\nAdding a space to the end and trying again.");
	boolean retryResult = addFinalSpaceAndTryAgain();
	alreadyTriedAddingFinalSpace = false; //reset
	return retryResult;
      }

      else {
	ParsingStatusUpdatedEvent updateEvent
	  = new ParsingStatusUpdatedEvent( this, session, false, errorIndex, errorText );
	distributeParsingStatusUpdates( updateEvent );
	ongoingStatus = false;
	return false;
      }
    }
  }


  //-------- Hack #1 ------
  /* Because on the Lisp side of our interface to the G2 parser we don't keep
   * around all of the heavy weight data structures that the classic editor
   * does, we are unable there to avail ourselves of the trick that the
   * classic editor uses to 'end' a parse successfully even when the final
   * token in the expression is a symbol (or fixnum, etc.) that hasn't got
   * a delimiter after it and so is deemed by the G2-side tokenizer to be
   * incomplete. For example, consider this expression as the value of
   * a rule: "uncondionally create a foo" -- unless we add a space after "foo"
   * the interface will declare that expression incomplete when we apply it.
   *   Since it's unnatural to insist that the user type that extra space
   * and its contrary to their reflexes if they've used the classic editor,
   * we incorporate this hack of adding the space for them in just the
   * situation where the G2-side compiler has rejected the the expression
   * as incomplete. The space will be included in the text of the result,
   * (not that anyone will notice) since there is no simple way to remove
   * it after the fact without doing gymnastics to keep our editor's dirty
   * bit from being set, gymnastics that don't seem warrented given the
   * amount of effort involved. (ddm 2/19/99)
   *
   *   This situation occurs when the error is found by the slot compiler
   * rather than the parser (whence the check that the error index is -1)
   * and the parse has been rejected by the slot compiler as incomplete.
   * We add the space and try the conclude again. Note that we're doing this
   * recursively from a call to conclude, and that we need to be a little
   * careful about the maintainance of the status information. To wit:
   * The status of the initial, triggering call to the conclude method is
   * ignored because we've gone down the then side of the conditional and
   * it is in the else. The status reported by the advance made by the
   * updateParseAnalysis call is going to be reported to the listeners,
   * however it will almost immediately be superceded by the status report
   * of the second, recursive call to attemptToConcludeParsingContext, which
   * will go into the else portion of the conditional, even if the result
   * from the slot compiler is unchanged, because the flag has been set
   * by the higher call to attempt... and doesn't get reset until the
   * recursive call returns, having issued its status report.
   */

  private static final String INCOMPLETE_PARSE = "this is incomplete";
  private boolean alreadyTriedAddingFinalSpace = false;

  private Item itemBeingConcluded;
  private Boolean editingForRuntimeChangeP;


  private boolean addFinalSpaceAndTryAgain() { 
    if (debug)
      System.out.println("Add Final Space hack: Calling addFinalSpaceAndTryAgain");
    updateParseAnalysis( lastTextSentToG2+" ", 
			 lastTextSentToG2.length() + 1,
			 true );

    alreadyTriedAddingFinalSpace = true;

    if (debug)
      System.out.println("Add Final Space hack: " +
			 "Returning result of recursive attemptToConcludeParsingContext");
    return ( attemptToConcludeParsingContext(itemBeingConcluded,
					     editingForRuntimeChangeP) );
  }





  /* ------ Hack #2 -------
   * There is a set of outstanding bugs that revolve around the G2-side getting
   * confused after you retreat into a string. The workaround is to move the
   * cursor just before the string and then move it just after so that the
   * entire interior of the string is parsed in one go. (This will probably
   * handle the intractible "..[X[i]].." bug as well.) This hack is to
   * do that workaround for the user automatically so that they never know
   * that there was a problem in the parser. Pushes the bugs under the rug
   * for now.
   *
   * The tracking bug for this was suggestion HQ-3141950
   *
   * The mechanics of the hack involve making calls to the parser while
   * we are in the middle of the processing of the initial call that
   * caused the problem. (We are inside unpackErrorInformation as it does
   * a test on errorIsInsideAString and then calls applyErrorInsideAStringHack.
   * That path through unpackErrorInformation will then return false, 
   * blocking the rest of the unpacking and distribution of the return
   * structure from the orgiginal, error-inside-a-string, call to the
   * parser.)
   *   The predicate that gates this hack also records the locations
   * of the beginning and ending of the string that we retreated into.
   */



  /* errorIsInsideAString starts at the beginning of the string and
   * matches double quotes looking for the errorIndex to be between
   * a string-pair of them. In principle we (sh/c)ould also notice
   * whether we are within a [..] expression inside the bounding
   * part of quotation marks, but that seems excessively cumbersome
   * for what we're trying to do here hacking around this flaw on
   * the G2-side. */
  private int posOfLastQuotesBeforeErrorIndex = 0;
  private int posOfQuoteAfterErrorIndex = 0;

  private boolean errorIsInsideAString(int errorIndex, String text) { 
    if ( text.indexOf("\"") == -1 ) // cheap, assuming they optimize it.
      return false;
    else {
      boolean inside = false;
      boolean stopOnNextQuote = false;
      /* indexOf is essentially doing just this, and this is easier to
       * write and manage than a while loop over searches for \". */
      for (int i = 0; i<text.length(); i++) {

	if ( i == errorIndex && inside )
	  stopOnNextQuote = true;

	if ( text.charAt(i) == '@' )
	  /* if we see the quote character, skip the next character
	   * since if they're quoting a quotation mark we'd should
	   * ignore that '"'. */
	  i++;
	else {
	  if ( text.charAt(i) == '\"' ) {
	    if (stopOnNextQuote) {
	      posOfQuoteAfterErrorIndex = i;
	      return true;
	    }
	    inside = !inside;
	    if (inside)
	      posOfLastQuotesBeforeErrorIndex = i;
	  }
	}
      }
    }
    return false; }


  /* The purpose of this flag is to keep us from looping. 
   * Before this flag was introduced I saw this happen on an advance
   * across a string that had an unbalanced '[' in it, where the
   * advance was inadvertant -- clicking back onto the window when
   * returning from another app. caused it. */
  private boolean retreatHackUnderway = false;


  private void applyErrorInsideAStringHack() {
    /* Record where we were originally going to land when we detected
     * this case so we can get back there at the end. */
    int originalTargetCursorPos = lastCursorPositionSentToG2;

    /* Note that we're underway. */
    retreatHackUnderway = true;

    /* Clear the pending error data. If it's still a (different) error
     * after we get back, the last pass will set these again. */
    errorIndex = -1;
    errorText = "";

    /* Retreat to just before the leading \". */
    if (debug)
      System.out.println("Hack #2: Retreating to " + posOfLastQuotesBeforeErrorIndex);
    updateParseAnalysis( lastTextSentToG2, // the whole text
			 posOfLastQuotesBeforeErrorIndex, // cursorPos
			 false,  // retreat
			 false); // do not report the results

    /* Then advance to just past the trailing \". */
    if (debug)
      System.out.println("Hack #2: Advancing to " + posOfQuoteAfterErrorIndex);
    updateParseAnalysis( lastTextSentToG2,
			 posOfQuoteAfterErrorIndex,
			 false,
			 false );

    /* And finally put us back where we were intending to go when
     * all this started. */
    if (debug)
      System.out.println("Hack #2: moving (back) to " + originalTargetCursorPos);
    updateParseAnalysis( lastTextSentToG2,
			 originalTargetCursorPos,
			 true );

    retreatHackUnderway = false;
  }


}
