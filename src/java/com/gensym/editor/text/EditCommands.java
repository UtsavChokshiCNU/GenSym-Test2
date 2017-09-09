/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 EditCommands.java
 *
 */
package com.gensym.editor.text;

import java.awt.Frame;
import java.awt.Event;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.util.Vector;
import javax.swing.KeyStroke;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

public class EditCommands extends AbstractStructuredCommand implements ServiceStateListener
{
  private Session session;

  private G2EditorWithUndo editor;
  private Vector structure = new Vector();

  private static final String shortResource = "CommandShortResource";
  private static final String longResource =  "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";

  private static Resource shortBundle = Resource.getBundle("com/gensym/editor/text/CommandShortResource");
  private static final String UNDO  = "Undo";
  private static final String REDO  = "Redo";
  private static final String CLEAR = "Clear";
  private static final String SEARCH = "Search";
  private static final String REPLACE = "Replace";
  private static final String GOTOERROR = "GoToError";
  private static final String GOTOLINE = "GoToLine";

  public EditCommands(Session session, G2EditorWithUndo editor){
    super(new CommandInformation[]{
      new CommandInformation(UNDO, false, shortResource, longResource,
			     "undo.gif", null, null, true, 
			     mnemonicResource, 
			     KeyStroke.getKeyStroke(KeyEvent.VK_Z, Event.CTRL_MASK)),
      new CommandInformation(REDO, false, shortResource, longResource,
			     "redo.gif", null, null, true, null, null),
      new CommandInformation(CLEAR, true, shortResource, longResource,
			     "clear.gif", null, null, true, null, null),
      new CommandInformation(SEARCH, true, shortResource, longResource,
			     "search.gif", null, null, false, 
			     mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_F, Event.CTRL_MASK)),
      new CommandInformation(REPLACE, true, shortResource, longResource,
			     null, null, null, false,
			     mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_H, Event.CTRL_MASK)),
      new CommandInformation(GOTOERROR, false, shortResource, longResource,
			     "goto_error.gif", null, null, true, null, null),
      new CommandInformation(GOTOLINE, true, shortResource, longResource,
			     null, null, null, false,
			     mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_G, Event.CTRL_MASK))
	});

    this.session = session;
    this.editor = editor;

    Vector group1 = new Vector();
    Vector group2 = new Vector();
    Vector group3 = new Vector();
    Vector group4 = new Vector();

    group1.addElement(UNDO);
    group1.addElement(REDO);
    group2.addElement(CLEAR);
    group3.addElement(SEARCH);
    group3.addElement(REPLACE);
    group4.addElement(GOTOERROR);
    group4.addElement(GOTOLINE);

    structure.addElement(group1);
    structure.addElement(group2);
    structure.addElement(group3);
    structure.addElement(group4);

    session.addServiceStateListener(this);
  }

  void removeBackPointers() {
    session = null;
    editor = null;
  }


  @Override
  public Vector getStructuredKeys() {
    return structure;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null)
      return;
    else if (cmdKey.equals(UNDO))
      handleUndoCommand();
    else if (cmdKey.equals(REDO))
      handleRedoCommand();
    else if (cmdKey.equals(CLEAR))
      handleClearCommand();
    else if (cmdKey.equals(SEARCH))
      handleSearchCommand();
    else if (cmdKey.equals(REPLACE))
      handleReplaceCommand();
    else if (cmdKey.equals(GOTOERROR))
      handleGoToErrorCommand();
    else if (cmdKey.equals(GOTOLINE))
      handleGoToLineCommand();
  }

  private void handleUndoCommand() {
    if ( session.theTextIsDirty() )
      editor.sendTextChangesToParser();
    editor.undo();
  }

  private void handleRedoCommand() {
    editor.redo();
  }

  private void handleClearCommand() {
    session.clearSession();
  }

  private void handleGoToErrorCommand() {
    editor.positionCursorAtError();
  }

  private void handleSearchCommand() {
    session.initiateTextSearchAndReplaceOn( (TextSearchTarget)editor );
  }

  private void handleReplaceCommand() {
    session.initiateReplaceRegionOn( (TextSearchTarget)editor );
  }

  private void handleGoToLineCommand() {
    session.installOrGoToLine();
  }


  @Override
  public void serviceStateChanged (ServiceStateEvent event) {
    String service = event.getService();

    if (service.equals(event.Undo))
      setAvailable(UNDO, event.getState());
    else if (service.equals(event.Redo))
      setAvailable(REDO, event.getState());
    else if (service.equals(event.GoToError))
      setAvailable(GOTOERROR, event.getState());

  }

}











