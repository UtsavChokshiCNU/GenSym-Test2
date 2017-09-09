/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ToolsCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Toolkit;
import java.awt.Image;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.util.Vector;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandEvent;

class ToolsCommands extends AbstractStructuredCommand{

  //Command Keys
  static final String BEAN_BUILDER = "ToolsBeanBuilder";
  static final String PREFERENCES = "ToolsPreferences";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";

  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private EditorFrame frame;

  ToolsCommands(EditorFrame frame){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("BeanGroup", new CommandInformation[]{
        new CommandInformation(BEAN_BUILDER, true, shortResource, longResource, 
			       null, null, null, false)}),
      new CommandGroupInformation("PreferencesGroup", new CommandInformation[]{
        new CommandInformation(PREFERENCES, true, shortResource, longResource, 
			     null, null, null, false)})});
    this.frame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }

    //System.out.println("ToolsCommands handling command key:"+cmdKey);
    if (cmdKey.equals(PREFERENCES)) doPreferences();
    else if (cmdKey.equals(BEAN_BUILDER)) doLaunchBeanBuilder();
  }

  private void doPreferences(){
    frame.getBeanEditTool().dirtyBit = true;
    Dimension size = frame.getSize();
    new ExpertBeanSheet(Preferences.currentPreferences, frame, size.width/4, size.height/4);
    Preferences.saveCurrentPreferences();
  }

  private void doLaunchBeanBuilder() {
    Runtime current = Runtime.getRuntime();
    try {
      String command = "java com.gensym.beanbuilder.G2BeanBuilder -logtofile";
      Process p = current.exec(command);
    }
    catch (java.io.IOException ex){
      com.gensym.message.Trace.exception(ex);
    }
  }
}

  

