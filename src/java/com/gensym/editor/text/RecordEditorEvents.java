/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RecordEditorEvents.java
 *
 */
package com.gensym.editor.text;

import java.awt.event.ActionEvent;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.Thread;
import java.lang.InterruptedException;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.menu.CMenuBar;
import com.gensym.ui.menu.CMenu;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.classes.Item;

/** This class mediates between text editing sessions and the record of the
 * parsing events that they issue. */

class RecordEditorEvents implements ParserInputEventListener, ParsingStatusUpdatedListener, RecordingPlaybackEventListener 
{
  
  private static final boolean debug = true;

  //---- locals -------
  private Recording r;

  private EditRecordCommands cmd;

  private TextView editor;
  private Session session;


  //---- i18n ---------
  private static final String shortResource = "CommandShortResource";
  private static final String longResource =  "CommandLongResource";

  private static Resource shortBundle
  = Resource.getBundle("com/gensym/editor/text/CommandShortResource");




  //---- constructor ------

  RecordEditorEvents(TextView editor, Session session) {
    r = new Recording();
    r.addPlaybackListener( this );
    this.editor = editor;
    this.session = session;
  }

  void initialize() {
    G2TextEditor frame = session.getFrame();
    CMenuBar mb = frame.getCMenuBar();
    setupEditRecordMenu(mb);
    clear(); // initializes the state and the availability of the actions.
  }
  

  //---- menu on the Editor's menubar ------------

  private void setupEditRecordMenu(CMenuBar editFrameMenuBar) {
    CMenu menu = new CMenu(shortBundle.getString("EditRecordMenu"));
    cmd = new EditRecordCommands();
    menu.add(cmd);
    editFrameMenuBar.add(menu);
  }

  
  private static final String CLEAR = "Clear";
  private static final String SAVE = "Save";
  private static final String PLAYBACK = "Playback";
  private static final String LOAD_AND_PLAYBACK = "LoadAndPlayback";

  class EditRecordCommands extends AbstractCommand {
    
    EditRecordCommands() {
      super( new CommandInformation[] {
	new CommandInformation
	  (CLEAR,  // key
	   false,   // initialAvailability
	   shortResource, // the name of this resource
	   longResource,  // ditto
	   null,   // smallImageName
	   null,   // largeImageName
	   null,   // initialState
	   true    // immediate
	    ),
	new CommandInformation(SAVE, false, shortResource, longResource,
			       null, null, null, true),
	new CommandInformation(PLAYBACK, false, shortResource, longResource,
			       null, null, null, true),
	new CommandInformation(LOAD_AND_PLAYBACK, true, shortResource, longResource,
			       null, null, null, true)
	  } );
    }

    /* This is a package private method inside AbstractCommand. This lets
     * me set the keys from the methods of the outer class without changing
     * the basic dictum since this 'public'ness is class internal. */
    @Override
    public void setAvailable(String cmdKey, boolean available) {
      super.setAvailable(cmdKey, available);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
      String cmdKey = e.getActionCommand();
      if (cmdKey == null)
	return;
      else if (cmdKey.equals(CLEAR))
	clear();
      else if (cmdKey.equals(SAVE))
	save();
      else if (cmdKey.equals(PLAYBACK))
	playback();
      else if (cmdKey.equals(LOAD_AND_PLAYBACK)) {
	clear();
	load();
	playback();
      }
    }
  }  // end EditRecordCommands inner class



  //---- Primary methods ------------

  private String originalText;
  private int originalCursorPos;

  /* Initializes the record to a snapshot of the current contents of the
   * editor.  Empties any ongoing record. */
  void clear() {
    originalText = editor.getText();
    originalCursorPos = editor.getCaretPosition();
    thereIsSomethingInTheRecord = false;
    cmd.setAvailable(PLAYBACK, false);
    cmd.setAvailable(SAVE, false);
    cmd.setAvailable(CLEAR, false);
    r.reset();
  }


  /* These are for updating the availability of the commands that
   * only make sense if there is a record. The method is called
   * with every ParserInputEvent. */
  boolean thereIsSomethingInTheRecord;

  void somethingWasRecorded() {
    if ( !thereIsSomethingInTheRecord ) {
      thereIsSomethingInTheRecord = true;
      cmd.setAvailable(PLAYBACK, true);
      cmd.setAvailable(SAVE, true);
      cmd.setAvailable(CLEAR, true);
    }
  }


  private final String testOutputNamestring = "d:\\editor events test.ser";
  void save() {
    try { 
      FileOutputStream fos = new FileOutputStream( testOutputNamestring );
      r.save(fos);
    } catch (FileNotFoundException e) {
      Trace.exception(e, "Could not open " + testOutputNamestring);
    } catch (IOException e) {
      Trace.exception(e);
    } 
    if (debug) {
    	System.out.println("Successfully saved");
    }
  }
  

  void load() {
    if (debug) {
    	System.out.println("Calling load");
    }
    try { 
      FileInputStream fis = new FileInputStream( testOutputNamestring );
      r = new Recording(fis);
    } catch (FileNotFoundException e) {
      Trace.exception(e, "Could not open " + testOutputNamestring);
    } catch (IOException e) {
      Trace.exception(e);
    }
    if (debug) {
    	System.out.println("Load finished");
    }
  }






  /* Runs the whole record back into the text editor at once. 
   */
  void playback() {
    /* Turn off the recording so the clear and reset events that follow
     * aren't noticed. */
    r.pause();

    /* Bring the whole session back to square one: an empty editor view
     * and no tokens on the parser's side, with prompts appropriate to 
     * position zero for the category being edited. */
    session.clearSession();

    /* Then put in the text that we started this recording with, sending
     * an AddRegion event to the parser. */
    editor.setText(originalText, originalCursorPos);

    /* Tell the record to send us the events. */
    r.playback();

    /* Pick up where we left off. */
    r.resume();
  }



  //---------- methods for RecordingPlaybackEventListener -----

  @Override
  public void handleRecordPlaybackEvent(RecordingPlaybackEvent e) {
    ParserInputEvent i = (ParserInputEvent)e.getObject();
    try { 
    	Thread.sleep(500); // half a second
    } catch (InterruptedException ex) {
      Trace.exception(ex);
    }
    editor.copyEventToTextView(i);
    editor.issueParserInputEvent(i, i.getID());
  }
    
      


  //----------- methods for ParserInputEventListener --------

  @Override
  public void cursorPositionChanged (ParserInputEvent e) { 
    somethingWasRecorded(); 
    r.add(e); }

  @Override
  public void characterAdded (ParserInputEvent e) {
    somethingWasRecorded(); 
    r.add(e); }

  @Override
  public void characterDeleted (ParserInputEvent e) { 
    somethingWasRecorded(); 
    r.add(e); }

  @Override
  public void regionAdded (ParserInputEvent e) { 
    somethingWasRecorded(); 
    r.add(e); }

  @Override
  public void regionDeleted (ParserInputEvent e) { 
    somethingWasRecorded(); 
    r.add(e); }

  @Override
  public void regionReplaced(ParserInputEvent e) { 
    somethingWasRecorded(); 
    r.add(e); }

  @Override
  public void replacedUnEqualRegions(ParserInputEvent e) { 
    somethingWasRecorded(); 
    r.add(e); }

  @Override
  public boolean attemptToConcludeParsingContext(Item item, 
						 Boolean editingForRuntimeChange) {
    //DMD FILL THIS IN WHEN YOU MAKE THIS WORK AGAIN
    return false;
  }

  //------------ method for ParsingStatusUpdatedListener -------

  /** Sends a listing of the record of events to System.out when there
   * is some problem with the text as a result of the last gesture sent
   * to the parser. */
  @Override
  public void changeParsingStatus(ParsingStatusUpdatedEvent e) {
    if ( !e.statusIsOkQ() )
      r.dump();
  }

}
