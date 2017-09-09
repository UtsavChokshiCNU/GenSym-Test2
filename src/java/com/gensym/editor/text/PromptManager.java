/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PromptManager.java
 *
 */
package com.gensym.editor.text;

import java.util.Enumeration;
import java.util.Locale;

import javax.swing.JList;
import javax.swing.ListModel;
import javax.swing.SwingUtilities;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.gensym.jgi.G2AccessException;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;


/** Dispatches a packet of prompt information that it receives from the
 * Parser to a set of views that it maintains.  Leaving the number and
 * type of prompts being dealt with implicit keeps it flexible for changes
 * that will inevitably come in the future.
 * @author David McDonald
 * @version 1.2
 */

// Made over for Swing 3/99.
// Moved facility that checks for true updates into G2SideParser 5/00

public class PromptManager implements ListSelectionListener, PromptsUpdatedListener 
{

  private boolean debug = false;
  private static boolean debugPromptInsertion = false;

  private int timeoutForMenuOfNamesLookup = 3000000; // virtually forever
  int getTimeoutForMenuOfNamesLookup() { return timeoutForMenuOfNamesLookup; }
  void setTimeoutForMenuOfNamesLookup(int t) { timeoutForMenuOfNamesLookup = t; }


  private TwAccess connection;

  private Session session;

  private CategoryView categoryView;
  CategoryView getCategoryView() { return categoryView; }
  void setCategoryView(CategoryView v) { categoryView = v; }

  private PromptView completionView;
  PromptView getCompletionView() { return completionView; }
  void setCompletionView(PromptView v) { completionView = v; }

  private PromptView categoryTokensView;
  PromptView getCategoryTokensView() { return categoryTokensView; }
  void setCategoryTokensView(PromptView v) { categoryTokensView = v; }

  private PromptsTarget targetView;
  PromptsTarget getTargetView() { return targetView; }
  void setTargetView(PromptsTarget v) { targetView = v; }

  void removeBackPointers() {
    connection = null;
    session = null;
    categoryView = null;
    completionView = null;
    categoryTokensView = null;
    targetView = null;
  }


  //----- trace setup ----
  private static MessageKey traceKey = Trace.registerMessageKey("com.gensym.editor.text",
								PromptManager.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.editor.text.TraceMessages", Locale.getDefault());
  






  //-------- constructor --------

  PromptManager (TwAccess connection, Session session) {
    this.connection = connection;
    this.session = session;
    categoryView = new CategoryView();
    completionView = new PromptView();
    categoryTokensView = new PromptView();
  }

  PromptManager() {}  // for the smoke test


  //------ Listening to the output of the parser -----------------

  /** This is the method that implements PromptsUpdatedListener.
   * It unpacks the event into the two kinds of prompts and
   * updates the corresponding views.
   */
  
  // Using synchronized to make sure that the events are scheduled at
  // the same time they are stored and SwingUtilities.ivokeLater() to avoid a
  // possible race condition which we believe is the cause of bug HQ-3668029.
  @Override
  public synchronized void updatePrompts(PromptsUpdatedEvent e) {
    lastScheduledUpdateEvent = e;
    SwingUtilities.invokeLater( new Updater(e));
  }

  void updateCompletionView(String[] prompts) {
    completionView.clear();
    populateList(completionView, prompts);
  }

  void updateCategoryView(String[] prompts) {
    categoryView.clear();
    populateList(categoryView, prompts);
  }

  // "volatile" is really here as documentation so other future users
  // know to be careful
  private volatile PromptsUpdatedEvent lastScheduledUpdateEvent;

  private class Updater implements Runnable {
    private PromptsUpdatedEvent event;
    
    Updater(PromptsUpdatedEvent e) {
      event = e;
    }

    @Override
    public void run() {
      // Only do the update if we are still the most recently
      // scheduled event
      if (event != null && event.equals(lastScheduledUpdateEvent)) {
		updateCategoryView(event.getCategoryPrompts());
		updateCompletionView(event.getCompletionPrompts());
      }
    }
  }




	  


  //----- Synchronized: the actual calls that populate the prompt views ----

  private volatile boolean promptChangeOperationUnderway = false;

  private void populateList(PromptView view, String[] prompts) {
    try {
      synchronized( this ) {
	if ( promptChangeOperationUnderway )
	  return;
	promptChangeOperationUnderway = true;
      }
      for (int i = 0; i < prompts.length; i++) {
	view.add( prompts[i] );
      }
    } finally {
      synchronized ( this ) {
	promptChangeOperationUnderway = false;
      }
    }
  }

  void clearAllPrompts() {
    try {
      synchronized( this ) {
	if ( promptChangeOperationUnderway )
	  return;
	promptChangeOperationUnderway = true;
      }
      categoryView.clear();
      completionView.clear();
      categoryTokensView.clear();
    } finally  {
      synchronized ( this ) {
	promptChangeOperationUnderway = false;
      }
    }
  }






  //--------- Managing Category Tokens ---------------------------

  /** This is the implementation of ListSelectionListener as called
   * from any of the prompt views. It dispatches on the identify of
   * the view. */
  @Override
  public void valueChanged(ListSelectionEvent e) {
    if ( e.getValueIsAdjusting() )
      return;
    JList l = (JList)e.getSource();
    if ( l.equals(categoryView) )
      categoryTokenSelected(l);
    else if ( l.equals(completionView)
	      || l.equals(categoryTokensView) )
      promptTokenSelected(l);
    else
      if (debug)
	System.out.println("List with selection is not one of the ones we know" +
			   "\n  " + l);
  }


  void categoryTokenSelected(JList l) {
    if ( !l.isSelectionEmpty() ) {
      session.putupWaitCursor();

      ListModel prompts = l.getModel();
      String prompt = (String)prompts.getElementAt( l.getSelectedIndex() );
      l.clearSelection(); // hmm--this has no immediate effect -repaint somehow?

      prompt = stripOffTheANY(prompt);
      categoryPromptSelected(prompt);  // does all the work

      session.putupDefaultCursor();
      categoryTokensView.requestFocus();
      return;
    }
  }

  private String stripOffTheANY(String originalCategoryPrompt) {
    String newPrompt = originalCategoryPrompt.substring(4);
    return newPrompt;
  }


  void categoryPromptSelected(String selectedCategory) {
    if ( categoryHasG2SideInstances(selectedCategory) )
      populateCategoryTokenPrompts(categoryTokenPrompts);
    else {
      categoryTokensView.clear();
    }
  }

  private void populateCategoryTokenPrompts(Sequence promptStrings) {
    if ( !categoryTokensView.empty() )
      categoryTokensView.clear();
    Enumeration list = categoryTokenPrompts.elements();
    while ( list.hasMoreElements() ) {
      Symbol element = (Symbol)list.nextElement();
      categoryTokensView.add( (element.toString()).toLowerCase() );
    }
  }


  /* categoryHasG2SideInstances stashes the prompts it retrieves (if any)
   * in here because it's return value is taken up with answering the
   * question of whether there were any prompts.
   */
  Sequence categoryTokenPrompts;

  /* Calls G2 and accesses the 'directory' that holds the instances.
   * Uses the existing G2-side accessor for this, so it gets back a
   * Sequence of strings (as with the other types of prompts).
   */
  private boolean categoryHasG2SideInstances(final String selectedCategory) {
    Integer handle = session.getParser().getParsingContext();   // cache this?
    String categoryName = selectedCategory.toUpperCase();
    if (debug)
      System.out.println("Selection: looking for instances of " + categoryName +
			 " in parsing context " + handle);
    Symbol categorySymbol = Symbol.intern(categoryName);
    Object[] args = new Object[2];
    args[0] = categorySymbol;
    args[1] = handle;
    
    Object returnValue;
    try { 
    	returnValue = connection.callRPC(_menuOfNamesForCategory, args,
					   timeoutForMenuOfNamesLookup); 
    } catch (G2AccessException ae) {
      // log something
      ae.printStackTrace();
      return false;
    }
    if (returnValue instanceof Boolean) { // has to be false given the code
      if (debug)
	System.out.println("Category selection: rpc returned False");
      return false;
    }
    else {
      if (returnValue instanceof Structure) {
	unpackCategoryPromptReturnStructure( (Structure)returnValue );
	return true;
      }
      else
	if (debug)
	  System.out.println("DDM: Unexpected return value from G2-menu-of-names-" +
			     "for-category:\n   " + returnValue);
      return false;
    }
  }
    
	
  protected static Symbol _menuOfNamesForCategory
                   = Symbol.intern("G2-MENU-OF-NAMES-FOR-CATEGORY");
  
  protected static Symbol _tokenPromptsForCategory
                   = Symbol.intern("TOKEN-PROMPTS-FOR-CATEGORY");



  private void unpackCategoryPromptReturnStructure(Structure ret) {
    try { 
    	categoryTokenPrompts = (Sequence)ret.getAttributeValue(_tokenPromptsForCategory); }
    catch (NoSuchAttributeException e) {
      e.printStackTrace();
      categoryTokenPrompts = null;
    }
  }








  //------- Managing the insertion of prompts into the text view -------
  
  /* This is the entry point from the ListSelectionEvent ValueChanged
   * method. It extracts the prompt from the list and then hands it
   * to insertPromptIntoTargetView to figure out exactly how much of
   * it (if any) we are going to insert into the target given the
   * context into which it is going to go.
   */
  void promptTokenSelected(JList l) {
    if ( !l.isSelectionEmpty() ) {
      session.putupWaitCursor();

      ListModel prompts = l.getModel();
      String prompt = (String)prompts.getElementAt( l.getSelectedIndex() );
      l.clearSelection();

      PromptManager.insertPrompt(prompt, targetView);

      session.putupDefaultCursor();
    }
  }


  /* Set by the right-side trimming code. It becomes true if all of
   * the left-trimmed prompt is contained within the right context
   * meaning that there's nothing to be inserted except possibly a
   * space. */
  private static boolean leftTrimmedPromptIsTotallySubsumed = false;

  /* This is set by the subroutine of th eleft trim operation that
   * is doing the overlap testing. It is looking for prefix match
   * against the prompt that this variable will hold it if there 
   * is any. */
  private static String leftSubstringMatch = "";

  /* That subroutine (matchLeadingSubstring) also manages this variable.
   * It tells us where within the left context a successful prefix match
   * happened and thereby where in that left context we should look for
   * the leading space if there is one. */
  private static int indexOfOverlapStartInLeftContext = 0;

  /* This reflects how much of the already-trimmed-on-its-left prompt
   * overlaps with some prefix of the right context. We trim this 
   * much off of the promt and insert the remainder.  */
  private static int numberOfCharactersToTrimFromRight = 0; 


  private static void initializePromptInsertionGlobals() {
    leftTrimmedPromptIsTotallySubsumed = false;
    synchronized (PromptManager.class) {
      leftSubstringMatch = "";
    }
    indexOfOverlapStartInLeftContext = 0;
    numberOfCharactersToTrimFromRight = 0;
  }



  /* Top level routine. Organizes the examination of the context and
   * defines the cases.
   */
  public static void insertPrompt(String prompt, PromptsTarget target) {
    if (debugPromptInsertion) {
    	System.out.println("\n\nPrompt = \"" + prompt + "\"");
    }

    initializePromptInsertionGlobals();

    /* first see if there's any overlap to the left and trim the prompt accordingly. */
    int lengthOfOriginalPrompt = prompt.length();
    String leftContext = target.getLeftPromptContext(lengthOfOriginalPrompt);
    String rightContext = target.getRightPromptContext(lengthOfOriginalPrompt);
    if (debugPromptInsertion)
      System.out.println("left context = \"" + leftContext + "\"" +
			 "\nright context = \"" + rightContext + "\"");

    String leftTrimmedPrompt = trimLeftPromptOverlap(prompt, leftContext);


    if ( leftTrimmedPrompt.length()==0 ) {
      /* This is the case where we are inserting foo into leftContext "foo" */
      if (debugPromptInsertion) {
    	  System.out.println("leftTrimmedPrompt of length 0");
      }
      moveOverOrIntroduceSpace(rightContext, target);
    }

    else {
      if (debugPromptInsertion) 
	System.out.println("leftTrimmedPrompt = \"" + leftTrimmedPrompt + "\"");

      /* Now see if there is some overlap of the remainder of the prompt with
       * the context to the right of the insertion point. */
      String rightTrimmedPrompt
	= trimRightPromptOverlap(leftTrimmedPrompt, rightContext);

      if ( leftTrimmedPromptIsTotallySubsumed ) {
	/* insert "foo bar" when the cursor is inside that very same string. */
	target.moveCursor( leftTrimmedPrompt.length() );
	moveOverOrIntroduceSpace(rightContext, target);
      }
      else if ( rightTrimmedPrompt.length()==0 )
	/* insert "foo bar" where the cursor is just before
	 * the 'f' in the right context "foo bar" */
	moveOverOrIntroduceSpace(rightContext, target);

      else if ( numberOfCharactersToTrimFromRight != 0 ) {
	/* Imagine the prompt is 'conclude that' and the cursor is between
	 * the 'd' and the 'e' with a right context of "e " */
	target.moveCursor( numberOfCharactersToTrimFromRight );
	target.insertPromptStringAtCursor(rightTrimmedPrompt);
	moveOverOrIntroduceSpace(rightContext, target);
      }
      else {
	/* This is the most frequent case where prompt are being inserted 
	 * at the end of the text extending it to the right. It also
	 * covers cases like inserting "foo bar baffle" into right: "foo bar". */
	introduceLeadingSpaceIfNeeded(target, leftContext);
	target.insertPromptStringAtCursor(rightTrimmedPrompt);
	moveOverOrIntroduceSpace(rightContext, target);
      }
    }
  }



  /* When a prompt is inserted there has to be one character of whitespace
   * following it; the cursor is positioned just after that space. This routine
   * add that space if it is not already part of the right context.
   */
  private static void moveOverOrIntroduceSpace(String rightContext, PromptsTarget target) {
    if ( rightContextBeginsWithSpace(rightContext) )
      target.moveCursor(1);
    else 
      target.insertPromptStringAtCursor(" ");
  }

  private static boolean rightContextBeginsWithSpace(String rightContext) {
    if ( rightContext.length()==0 ) // we're at the right end of the whole text
      return false;
    else
      return (rightContext.charAt(0)==' ');
  }


  /* Similarly, there has to be a space between the beginning of the prompt
   * and the previous token. The sole exception is when the prompt is being
   * inserted at the beginning of a line.
   */
  private static void introduceLeadingSpaceIfNeeded(PromptsTarget target, String leftContext) {
    if (debugPromptInsertion)
      System.out.println("indexOfOverlapStartInLeftContext = " +
			 indexOfOverlapStartInLeftContext);
    if ( ! (leftContext.length() == 0 ) ) {
    	
    	boolean condition = indexOfOverlapStartInLeftContext == 0 && ! (leftContext.endsWith(" ") || leftContext.endsWith("\n"));
    	condition = condition || (indexOfOverlapStartInLeftContext > 0 && leftContext.charAt(indexOfOverlapStartInLeftContext - 1) == ' ' 
        			&& leftContext.charAt(indexOfOverlapStartInLeftContext - 1) == '\n');
    	
        if (condition)
    		target.insertPromptStringAtCursor(" ");
    }
  }



  /* Take the original, entire prompt and see where there is some overlap
   * (match) between a suffix of the left context and a prefix of the prompt. 
   */
  private static synchronized String trimLeftPromptOverlap(String prompt, String leftContext) {
    /* on the chance that the VM has a fast implementation of this it's a easy case. */
    if (prompt.equals(leftContext))
      return "";
    else {
      int indexOfFirstLetterMatch = -1;
      leftSubstringMatch = ""; // reinitialize
      char promptsFirstLetter = prompt.charAt(0);
      for (int i=0; i<leftContext.length(); // it may be smaller than the prompt
	   i++ ) {
	if ( leftContext.charAt(i)==promptsFirstLetter ) {
	  indexOfFirstLetterMatch = i;
	  if ( matchLeadingSubstring(prompt, leftContext.substring(i)) )
	    break;
	}
      }
      if (!leftSubstringMatch.equals("")) // we've got something
	return prompt.substring( leftSubstringMatch.length() );	
      else 
	return prompt;
    }
  }

  /* Subroutine of trimLeftPromptOverlap that does the actual match checking
   * at an index within the left context established by its parent. 
   */ 
  private static synchronized boolean matchLeadingSubstring(String prompt, String rightEndOfContext) {
    indexOfOverlapStartInLeftContext = 0;
    if (debugPromptInsertion)
      System.out.println("Index " + indexOfOverlapStartInLeftContext +
			 " matchLeadingSubstring: \"" + prompt +
			 "\" against \"" + rightEndOfContext);
    for (int i=0; i<rightEndOfContext.length(); i++) {
      if ( prompt.charAt(i) != rightEndOfContext.charAt(i) )
	return false;
      else
	// suspicious side effect in case of repetitive prompts and contexts
	indexOfOverlapStartInLeftContext++;
    } 
    leftSubstringMatch = prompt.substring(0, indexOfOverlapStartInLeftContext);
    if (debugPromptInsertion)
      System.out.println("This much matched: \"" + leftSubstringMatch + "\"" +
			 "\n match started at " + indexOfOverlapStartInLeftContext);
    return true;
  }





  /** This determines whether there is some prefix of the right context
   * that matches some prefix of the now trimmed-from-the-left prompt.
   * Most of what it finds out is communicated to the cordinating parent
   * method through globals (see earlier descriptions). It also returns a
   * string that will be the net prompt that's inserted into the target
   * at a position determined by the values of the additional variables. 
   */
  private static String trimRightPromptOverlap(String leftTrimmedPrompt, String rightContext) {
    leftTrimmedPromptIsTotallySubsumed = false; // initialization
    if (debugPromptInsertion)
      System.out.println("Trimming on the right:" +
			 "\nleftTrimmedPrompt is \"" + leftTrimmedPrompt +
			 "\" of length " + leftTrimmedPrompt.length() +
			 "\nrightContext = \"" + rightContext + "\" of length " +
		       rightContext.length());
    int maxSearchLength = 0;
    if ( leftTrimmedPrompt.length() < rightContext.length() )
      maxSearchLength = leftTrimmedPrompt.length();
    else 
      maxSearchLength = rightContext.length();
    if (debugPromptInsertion)
      System.out.println("maxSearchLength = " + maxSearchLength);

    numberOfCharactersToTrimFromRight = 0;
    for (int i=0; i<maxSearchLength; i++) {
      if ( leftTrimmedPrompt.charAt(i) == rightContext.charAt(i) )
	numberOfCharactersToTrimFromRight++;
      else
	break;
    }
    if (debugPromptInsertion)
      System.out.println("numberOfCharactersToTrimFromRight = " + 
			 numberOfCharactersToTrimFromRight);
    if ( numberOfCharactersToTrimFromRight == leftTrimmedPrompt.length() ) {
      /* This case corresponds to being in the middle of a already introduced
       * multi-token prompt. It's hard to imagine this being a motivated case,
       * but it's logically possible. */
      leftTrimmedPromptIsTotallySubsumed = true;
      return "";
    }
    else if ( numberOfCharactersToTrimFromRight != 0 )
      return leftTrimmedPrompt.substring(numberOfCharactersToTrimFromRight);
    else
      return leftTrimmedPrompt;
  }



}
  
