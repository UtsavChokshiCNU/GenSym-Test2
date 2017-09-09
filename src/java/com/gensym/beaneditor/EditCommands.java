/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 EditCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.beans.Introspector;
import java.beans.BeanDescriptor;
import java.beans.BeanInfo;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;

class EditCommands extends AbstractStructuredCommand{

  //Command Keys
  static final String CUT = "EditCut";
  static final String COPY = "EditCopy";
  static final String PASTE = "EditPaste";
  static final String DELETE = "EditDelete";
  static final String SELECT_ALL = "EditSelectAll";
  static final String PROPERTIES = "EditProperties";
  static final String EDIT = "EditEdit";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private EditorFrame frame;

  EditCommands(EditorFrame frame){
    super(new StructuredCommandInformation[]{
      new CommandGroupInformation("CutCopyPaste", new CommandInformation[]{
        new CommandInformation(CUT, true, shortResource, longResource, "cut.gif",
			       null, null, true),
        new CommandInformation(COPY, true, shortResource, longResource, "copy.gif",
			       null, null, true),
        new CommandInformation(PASTE, true, shortResource, longResource, "paste.gif",
			       null, null, true)}),
      new CommandGroupInformation("Delete&Select", new CommandInformation[]{
        new CommandInformation(DELETE, true, shortResource, longResource, null,
			       null, null, true),
        new CommandInformation(SELECT_ALL, true, shortResource, longResource, null,
			       null, null, true)}),
      new CommandGroupInformation("Properties", new CommandInformation[]{
        new CommandInformation(EDIT, true, shortResource, longResource, null,
			       null, null, false),
        new CommandInformation(PROPERTIES, true, shortResource, longResource, null,
			       null, null, false)})});
    this.frame = frame;
    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }

    //System.out.println("EditCommands handling command key:"+cmdKey);
    if (cmdKey.equals(CUT)){}
    else if (cmdKey.equals(COPY)){}
    else if (cmdKey.equals(PASTE)){}
    else if (cmdKey.equals(DELETE)) frame.getBeanEditTool().deleteSelection();
    else if (cmdKey.equals(SELECT_ALL)) frame.getBeanEditTool().selectAll();
    else if (cmdKey.equals(PROPERTIES)) frame.getBeanEditTool().editLastSelection();
    else if (cmdKey.equals(EDIT)) frame.getBeanEditTool().runCustomizerOnLastSelection ();
  }

  void updateAvailability(){
    //For now, keep cut/copy/paste always disabled
    setAvailable(CUT, false);
    setAvailable(COPY, false);
    setAvailable(PASTE, false);

    BeanCanvas canvas = frame.getCanvas();
    if (canvas != null && frame.application.inDesignMode()){
      setAvailable(DELETE, frame.getBeanEditTool().selectionExists());
      setAvailable(SELECT_ALL, true); 
      boolean selectionCountEqualsOne = frame.getBeanEditTool().selectionCount() == 1;
      setAvailable(PROPERTIES, selectionCountEqualsOne);
      if (selectionCountEqualsOne){
	try {
	  Component[] selection = frame.getBeanEditTool().getSelection();
	  Wrapper wrapper = (Wrapper)selection[0];
	    BeanInfo bi = Introspector.getBeanInfo (wrapper.bean.getClass ());
	  BeanDescriptor bd = bi.getBeanDescriptor ();
	  setAvailable(EDIT, bd.getCustomizerClass () != null);
	} catch (Exception e) {
	  Trace.exception (e);
	  setAvailable(EDIT, false);
	}
      }
      else
	setAvailable(EDIT, false);
    }
    else{
      setAvailable(DELETE, false);
      setAvailable(SELECT_ALL, false); 
      setAvailable(PROPERTIES, false);
      setAvailable(EDIT, false);
    }    
  }
}
