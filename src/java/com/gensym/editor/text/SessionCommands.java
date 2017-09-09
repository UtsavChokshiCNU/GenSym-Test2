/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SessionCommands.java
 *
 */
package com.gensym.editor.text;

import java.awt.Container;
import java.awt.Frame;
import java.awt.Event;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.util.Vector;
import javax.swing.KeyStroke;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

public class SessionCommands extends AbstractStructuredCommand implements ServiceStateListener
{
  private Container appFrame;  // had been frame
  private Vector structure = new Vector();

  private Session session;

  private static final String shortResource = "CommandShortResource";
  private static final String longResource =  "CommandLongResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/editor/text/CommandShortResource");

  public static final String APPLY_AND_EXIT = "ApplyAndExit";
  public static final String APPLY          = "Apply";
  public static final String EXIT           = "Exit";

  public SessionCommands(Container frame, Session session){
    super(new CommandInformation[]{
      /* Exit is initially available since you can always exit the editor.
       * Apply and Apply_and_exit are initially unavailable since they
       * only make sense if there's been some change to the text. */
      new CommandInformation
	(APPLY_AND_EXIT, false, 
	 shortResource, longResource, "applyexit.gif",
	 null, null, true,
	 null, // string: mnemonicResourceName
	 KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, Event.CTRL_MASK)),
      new CommandInformation
	(APPLY, false, 
	 shortResource, longResource, "apply.gif",
	 null, null, true,
	 null, null ),
      new CommandInformation
	(EXIT, true, 
	 shortResource, longResource, "exit.gif",
	 null, null, true,
	 null, // string: mnemonicResourceName
	 KeyStroke.getKeyStroke(KeyEvent.VK_Q, Event.CTRL_MASK)
	  )});

    Vector group1 = new Vector();
    Vector group2 = new Vector();

    group1.addElement(APPLY_AND_EXIT);
    group1.addElement(APPLY);
    group2.addElement(EXIT);

    structure.addElement(group1);
    structure.addElement(group2);

    this.appFrame = frame;
    this.session = session;

    session.addServiceStateListener(this);
  }

  void removeBackPointers() {
    appFrame = null;
    session = null;
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
    else if (cmdKey.equals(APPLY_AND_EXIT))
      handleApplyAndExitCommand();
    else if (cmdKey.equals(APPLY))
      handleApplyCommand();
    else if (cmdKey.equals(EXIT))
      handleExitCommand();
  }

  private void handleApplyAndExitCommand() {
    session.attemptToConcludeTextThenExit();
  }

  private void handleApplyCommand() {
    session.attemptToConcludeText();
  }

  private void handleExitCommand() {
    if (isAvailable(APPLY))
      session.launchConfirmCancelDialog();
    else
      session.shutdownSession(false);
  }


  @Override
  public void serviceStateChanged (ServiceStateEvent event) {
    String service = event.getService();

    if (service.equals(event.ApplyChanges)) {
      setAvailable(APPLY, event.getState());
      setAvailable(APPLY_AND_EXIT, event.getState());
    }
  }



}

