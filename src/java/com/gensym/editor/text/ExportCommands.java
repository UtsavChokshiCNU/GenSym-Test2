/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ExportCommands.java
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

public class ExportCommands extends AbstractStructuredCommand implements ServiceStateListener
{
  private Container appFrame;  // had been frame
  private Vector structure = new Vector();

  private Session session;

  private G2Editor editor;
  void setEditor(G2Editor e) { editor = e; }

  private static final String shortResource = "CommandShortResource";
  private static final String longResource =  "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/editor/text/CommandShortResource");

  public static final String LOAD           = "Load";
  public static final String SAVE           = "Save";
  public static final String PRINT          = "Print";

  public ExportCommands(Container frame, Session session, G2Editor editor){
    super(new CommandInformation[]{
      new CommandInformation(LOAD,  // key
			     true,  // initialAvailability
			     shortResource, 
			     longResource, 
			     null,  // smallImageName
			     null,  // largeImageName
			     null,  // initialState
			     true,   // immediate
			     mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_O, Event.CTRL_MASK)),
      new CommandInformation(SAVE, true,
			     shortResource, longResource, null,
			     null, null, true,
			     mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_S, Event.CTRL_MASK)),
      new CommandInformation(PRINT, true,
			     shortResource, longResource, null,
			     null, null, true,	
			     mnemonicResource,
			     KeyStroke.getKeyStroke(KeyEvent.VK_P, Event.CTRL_MASK))
			     });

    Vector group1 = new Vector();

    group1.addElement(LOAD);
    group1.addElement(SAVE);
    group1.addElement(PRINT);

    structure.addElement(group1);

    this.appFrame = frame;
    this.session = session;
    this.editor = editor;

    session.addServiceStateListener(this);
  }

  void removeBackPointers() {
    appFrame = null;
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
    else if (cmdKey.equals(LOAD))
      handleLoadCommand();
    else if (cmdKey.equals(SAVE))
      handleSaveCommand();
    else if (cmdKey.equals(PRINT))
      handlePrintCommand();
  }

  private void handleLoadCommand() {
    session.selectAndLoadFileIntoEditor();
  }

  private void handleSaveCommand() {
    session.saveEditorTextToFile();
  }

  private void handlePrintCommand() {
    session.printEditorContents();
  }



  @Override
  public void serviceStateChanged (ServiceStateEvent event) {
    String service = event.getService();
    if (service.equals(event.Load))
      setAvailable(LOAD, event.getState());
    if (service.equals(event.Save))
      setAvailable(SAVE, event.getState());
    if (service.equals(event.Print))
      setAvailable(PRINT, event.getState());
  }



}











