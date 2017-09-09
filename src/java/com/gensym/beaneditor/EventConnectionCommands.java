package com.gensym.beaneditor;

import java.awt.Component;
import java.awt.Menu;
import java.awt.MenuItem;
import java.awt.Image;
import java.awt.Color;
import java.awt.Point;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.beans.*;
import java.util.Vector;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.menu.awt.CMenu;
import com.gensym.message.Resource;

class EventConnectionCommands extends AbstractStructuredCommand{

  static final String DELETE = "DeleteEventConnection";
  static final String EDIT = "EditEventConnection";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private Object popupElement;
  private EditorFrame frame;

    EventConnectionCommands(EditorFrame frame)
    {
      super(new StructuredCommandInformation[]{
	new CommandGroupInformation("Delete", new CommandInformation[]{
	  new CommandInformation(DELETE, true, shortResource, 
				 longResource, null, null, null, true)}),
	new CommandGroupInformation("Edit", new CommandInformation[]{
	  new CommandInformation(EDIT, true, shortResource, 
				 longResource, null, null, null, false)})});

	this.frame = frame;
        updateAvailability();
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent)
    {
        String cmdKey = actionEvent.getActionCommand();
        if (cmdKey == null) return;
        if (!isAvailable(cmdKey))
            throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
	else if (cmdKey.equals(DELETE)) doDelete();
	else if (cmdKey.equals(EDIT)) doEdit();
    }

  private void doDelete(){
    if (popupElement instanceof Port)
      frame.getBeanEditTool().deletePort((Port)popupElement);
    else if (popupElement instanceof EventConnection){
      EventConnection connection = (EventConnection)popupElement;
      connection.input.removeLink();
      frame.updateViewMenuForDelete(connection.input);
    }
    else if (popupElement instanceof LooseEnd){
      EventConnection connection = ((LooseEnd)popupElement).getConnection();
      connection.input.removeLink();
      frame.updateViewMenuForDelete(connection.input);
    }
  }

  private void doEdit(){
    //System.out.println("popupElement = "+popupElement);
    Port inputPort = null;
    if (popupElement instanceof Port)
      {
	Port port = (Port) popupElement;
	if (port.getIsInput())
	  inputPort = port.getConnection().input;
	else
	  inputPort = port;
      }
    else if (popupElement instanceof EventConnection){
      EventConnection connection = (EventConnection)popupElement;
      inputPort = connection.input;
    }
    else if (popupElement instanceof LooseEnd)
      {
	EventConnection connection = ((LooseEnd)popupElement).getConnection();
	inputPort = connection.input;
      }
    if (inputPort != null)
      inputPort.editExistingHookup();
  }

  void setPopupElement(Object element){
    popupElement = element;
    updateAvailability();
  }

  void updateAvailability(){
  // Christine, the command availability of EDIT is based
  // on whether:
  //  1) The hookup is complete, i.e. input connection and output exist
  //  AND
  //  2) sourceSyntax of the input port is HookupFactory.G2SCRIPT or HookupFactory.JAVA
    EventConnection connection;
    Port inputPort = null;
    if (popupElement instanceof Port){
	Port port = (Port) popupElement;
	connection = port.getConnection();
    }
    else if (popupElement instanceof EventConnection){
      connection = (EventConnection)popupElement;
    }
    else if (popupElement instanceof LooseEnd){
	connection = ((LooseEnd)popupElement).getConnection();
    }
    else{
      setAvailable(EDIT, false);
      return;
    }
    inputPort = connection.input;
    if (inputPort != null  && connection.output != null &&
	((inputPort.getSyntax() == HookupFactory.G2SCRIPT) ||
	 (inputPort.getSyntax() == HookupFactory.JAVA)))
      setAvailable(EDIT, true);
    else 
      setAvailable(EDIT, false);
      
  }

}
