/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ViewCommands.java
 *
 */
package com.gensym.editor.text;

import java.awt.Component;
import java.awt.Frame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import java.awt.event.ActionEvent;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

public class ViewCommands extends AbstractCommand
{
  private G2TextEditor appFrame;
  private G2Editor editor;
  private Session session;

  private static final String shortResource = "CommandShortResource";
  private static final String longResource =  "CommandLongResource";
  private static Resource shortBundle = Resource.getBundle("com/gensym/editor/text/CommandShortResource");

  static final String UNICODE         = "Unicode";
  static final String FONTCHOOSER     = "FontChooser";
  static final String TOOLBAR         = "ToolBar";
  static final String LANGUAGEPROMPTS = "LanguagePrompts";
  static final String ITEMTYPES       = "ItemTypes";
  static final String ITEMNAMES       = "ItemNames";
  static final String ITEMS_AND_NAMES = "ItemsAndNames";
  static final String STATUS          = "Status";
  static final String LINEWRAP        = "LineWrap";

  public ViewCommands(G2TextEditor frame, Session session, G2Editor editor){
    super( new CommandInformation[] {

      new CommandInformation
	(UNICODE, //the key
	 true,    // whether it is initially available
	 shortResource, // name of the (short) resource file
	 longResource,  // ditto
	 null, // name of image file for its small icon
	 null, // large icon
	 Boolean.FALSE, // initial state: is this command selected (on) ?
	 true // is it immediate, i.e. does it execute without further user interaction?
	  ),

	new CommandInformation(FONTCHOOSER, true, shortResource, longResource, null,
			       null, Boolean.FALSE, true),
        new CommandInformation(TOOLBAR, true, shortResource, longResource, null,
			       null, Boolean.TRUE, true),
	new CommandInformation(LANGUAGEPROMPTS, true, shortResource, longResource, null,
			       null, Boolean.TRUE, true),
	//      new CommandInformation(ITEMNAMES, true, shortResource, longResource, null,
	//			     null, Boolean.TRUE, true),
	//      new CommandInformation(ITEMTYPES, true, shortResource, longResource, null,
	//			     null, Boolean.TRUE, true),
	// ddm--Retaining this code to save typing should we revert to separate cases.
	new CommandInformation(ITEMS_AND_NAMES, true, shortResource, longResource, null,
			       null, Boolean.TRUE, true),
	new CommandInformation(STATUS, true, shortResource, longResource, null,
			       null, Boolean.TRUE, true),
	new CommandInformation(LINEWRAP, true, shortResource, longResource, null, null,
			       new Boolean( ((JTextArea)editor).getLineWrap() ), true)
	});
    this.appFrame = frame;
    this.session = session;
    this.editor = editor;
  }

  void removeBackPointers() {
    appFrame = null;
    session = null;
    editor = null;
  }




  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null)
      return;
    else if (cmdKey.equals(UNICODE))
      handleUnicodeCommand();
    else if (cmdKey.equals(FONTCHOOSER))
      handleFontChooserCommand();
    else if (cmdKey.equals(TOOLBAR))
      handleToolBarCommand();
    else if (cmdKey.equals(LANGUAGEPROMPTS))
      handleLanguagePromptsCommand();
    //    else if (cmdKey.equals(ITEMTYPES))
    //      handleItemTypesCommand();
    //    else if (cmdKey.equals(ITEMNAMES))
    //      handleItemNamesCommand();
    else if (cmdKey.equals(ITEMS_AND_NAMES))
      handleItemsAndNamesCommand();
    else if (cmdKey.equals(STATUS))
      handleStatusCommand();
    else if (cmdKey.equals(LINEWRAP))
      toggleLineWrap();
  }

  private void handleUnicodeCommand() {
    if ( appFrame.UnicodeWidgetInstalled() )
      appFrame.removeUnicodeWidget();
    else
      appFrame.installUnicodeWidget();
  }

  private void handleFontChooserCommand() {
    if ( appFrame.fontChooserIsVisible )
      appFrame.removeFontChooser();
    else
      appFrame.installFontChooser();
  }

  private void handleToolBarCommand() {
    Component toolBar = appFrame.getToolBar();
    toolBar.setVisible(!(toolBar.isVisible()));
    appFrame.validate();
  }

  private void handleLanguagePromptsCommand() {
    JPanel p = appFrame.getCompletionPanel();
    p.setVisible(!(p.isVisible()));
    appFrame.validate();
  }

  private void handleItemsAndNamesCommand() {
    JPanel p = appFrame.getCategoryPanel();
    p.setVisible(!(p.isVisible()));
    JPanel q = appFrame.getItemsPanel();
    q.setVisible(!(q.isVisible()));
    appFrame.validate();
  }

  private void handleItemTypesCommand() {
    JPanel p = appFrame.getCategoryPanel();
    p.setVisible(!(p.isVisible()));
    appFrame.validate();
  }

  private void handleItemNamesCommand() {
    JPanel p = appFrame.getItemsPanel();
    p.setVisible(!(p.isVisible()));
    appFrame.validate();
  }

  private void handleStatusCommand() {
    JPanel statusBar = appFrame.getStatusBar();
    statusBar.setVisible(!(statusBar.isVisible()));
    appFrame.validate();
  }

  private void toggleLineWrap() {
    JTextArea editorPrime = (JTextArea)editor; 
    boolean currentValue = editorPrime.getLineWrap();
    editorPrime.setLineWrap( !currentValue );
  }

  void makeFontChooserUnselected() {
    setState(FONTCHOOSER, new Boolean(false));
  }

}











