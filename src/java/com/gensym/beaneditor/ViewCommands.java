/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ViewCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Image;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.CommandEvent;
import com.gensym.draw.BasicDrawElement;

class ViewCommands extends AbstractStructuredCommand{

  //Command Keys
  private static final String TOOLBAR = "ViewToolBar";
  private static final String STATUS_BAR = "ViewStatusBar";
  private static final String DEBUG_WINDOW = "ViewDebugWindow";
  private static final String EVENTS = "ViewEvents";
  private static final String ALL_EVENTS = "ViewAllEvents";
  private static final String FRIENDS = "ViewFriends";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private Hashtable eventTable;
  private EditorFrame frame;
  private Vector eventList = new Vector();

  private StructuredCommandInformation[] structure;
  private CommandGroupInformation  allEvents;
  private CommandInformation friends;

  ViewCommands(EditorFrame frame){
    super(new StructuredCommandInformation[]{});

    CommandGroupInformation toolBarAndStatusBar = 
      new CommandGroupInformation("ToolBar&StatusBar", new CommandInformation[]{
        new CommandInformation(TOOLBAR, true, shortResource, longResource, null, 
			       null,new Boolean(frame.getToolBarPanel().isVisible()),
			       true),
        new CommandInformation(STATUS_BAR, true, shortResource, longResource, null, 
			       null, new Boolean(frame.getStatusBar().isVisible()),
			       true)});

    CommandGroupInformation debugWindow =
      new CommandGroupInformation("DebugWindow", new CommandInformation[]{
	new CommandInformation(DEBUG_WINDOW, true, shortResource, longResource, null,
			       null, Boolean.FALSE,
			       true)});

    allEvents = new CommandGroupInformation("AllEvents", new CommandInformation[]{
      new CommandInformation(ALL_EVENTS, true, shortResource, longResource, 
			     null, null, Boolean.TRUE, true)});

    friends =
      new CommandInformation(FRIENDS, true, shortResource, longResource,
			     null, null, Boolean.TRUE, true);

    structure = new StructuredCommandInformation[3];
    structure[0] = toolBarAndStatusBar;
    structure[1] = debugWindow;
    this.frame = frame;
    eventTable = new Hashtable();
    updateStructure();
  }

  private void updateStructure(){
    CommandInformation[] events = new CommandInformation[eventList.size()];
    CommandInformation commandInfo;
    for (int i=0; i<eventList.size(); i++){
      String event = (String)eventList.elementAt(i);
      Boolean visible = Boolean.TRUE;
      EventInformation eventInfo = (EventInformation)eventTable.get(event);
      if (!eventInfo.visible) visible = Boolean.FALSE;
      commandInfo = new CommandInformation(event, true, null, null, null, null,
					   visible, true, event, event, null, 
					   null);
      events[i] = commandInfo;
    }
    CommandGroupInformation eventsGroup = 
      new CommandGroupInformation("Events", new CommandInformation[]{
        new SubCommandInformation(EVENTS, true, shortResource, longResource, null, 
				  null, null, new StructuredCommandInformation[]{
	          allEvents, 
		  new CommandGroupInformation("IndividualEvents", events)}),
	friends});;
    structure[2] = eventsGroup;
    setStructuredKeys(structure);
    setAvailable(EVENTS, !eventTable.isEmpty());
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }

    //System.out.println("ViewCommands handling command key:"+cmdKey);
    if (cmdKey.equals(TOOLBAR)){
      BeanToolBarPanel toolBar = frame.getToolBarPanel();
      toolBar.setVisible(!toolBar.isVisible());
      if (toolBar.isVisible())
	setState(TOOLBAR, Boolean.TRUE);
      else
	setState(TOOLBAR, Boolean.FALSE);
      frame.validate();
    }
    else if (cmdKey.equals(STATUS_BAR)){
      BeanStatusBar statusBar = frame.getStatusBar();
      statusBar.setVisible(!statusBar.isVisible());
      if (statusBar.isVisible())
	setState(STATUS_BAR, Boolean.TRUE);
      else
	setState(STATUS_BAR, Boolean.FALSE);
      frame.validate();
    }
    else if (cmdKey.equals(DEBUG_WINDOW)){
      boolean visible = frame.isDebugWindowVisible();
      frame.setDebugWindowVisible(!visible);
      if (!visible)
	setState(DEBUG_WINDOW, Boolean.TRUE);
      else
	setState(DEBUG_WINDOW, Boolean.FALSE);
    }
    else if (cmdKey.equals(ALL_EVENTS)){
      setAllEventsVisible();
      frame.getCanvas().repaintIt();
    }
    else if (eventList.contains(cmdKey)){
      setEventsVisible(cmdKey);
      frame.getCanvas().repaintIt();
    }
    else if (cmdKey.equals(FRIENDS)){
      Boolean state = getState(FRIENDS);
      boolean visible = state.booleanValue();
      Enumeration links = KnowledgeLink.links.elements();
      BeanCanvas canvas = frame.getCanvas();
      while (links.hasMoreElements()){
	KnowledgeLink link = (KnowledgeLink)links.nextElement();
	link.setVisible(!visible);
	canvas.invalidateElement(link);
	if (link.object instanceof KnowledgeLinkLooseEnd){
	  KnowledgeLinkLooseEnd end = (KnowledgeLinkLooseEnd)link.object;
	  end.setVisible(!visible);
	  canvas.invalidateElement(end);
	}
      }
      setState(FRIENDS, (visible ? Boolean.FALSE : Boolean.TRUE));
    }
  }

  void addEvent(Port port){
    String event = port.getEventInfo().name;
    EventInformation eventInfo = (EventInformation)eventTable.get(event);
    if (eventInfo != null){
      eventInfo.eventList.addElement(port);
      if ((eventInfo.visible) && (!port.isVisible())){
	eventInfo.visible = false;
	setState(event, Boolean.FALSE);
	setState(ALL_EVENTS, Boolean.FALSE);
      }
    }
    else{
      EventInformation newEventInfo = new EventInformation();
      newEventInfo.eventList.addElement(port);
      newEventInfo.name = event;
      newEventInfo.visible = port.isVisible();
      eventTable.put(event, newEventInfo);
      eventList.addElement(event);
      updateStructure();
    }
  }

  void removeEvent(Port port){
    String event;
    if (port.getIsInput())
      port = port.getConnection().input;
    event = port.getEventInfo().name; 
   
    EventInformation eventInfo = (EventInformation)eventTable.get(event);
    if (eventInfo != null){
      eventInfo.eventList.removeElement(port);
      if (eventInfo.eventList.size() == 0){
	eventTable.remove(event);
	eventList.removeElement(event);
      }
      updateStructure();
    }
  }

  private void setPortVisible(Port port, boolean visible){
    port.setVisible(visible);
    frame.getCanvas().invalidateElement(port);
    EventConnection cxn = port.getConnection();
    cxn.setVisible(visible);
    frame.getCanvas().invalidateElement(cxn);
    cxn.output.setVisible(visible);
    frame.getCanvas().invalidateElement((BasicDrawElement)cxn.output);
  }

  private void setEventsVisible(EventInformation eventInfo, boolean visible){
    Enumeration events = eventInfo.eventList.elements();
    while (events.hasMoreElements()){
      Port port = (Port)events.nextElement();
      setPortVisible(port, visible);
    } 
    eventInfo.visible = visible;
    setState(eventInfo.name, new Boolean(visible));
  }

  private void setEventsVisible(String event){
    EventInformation eventInfo = (EventInformation)eventTable.get(event);
    setEventsVisible(eventInfo, !eventInfo.visible);
    if (!eventInfo.visible) setState(ALL_EVENTS, Boolean.FALSE);
    else updateEventState();
  }

  private void setAllEventsVisible(){
    boolean visible = !(getState(ALL_EVENTS).booleanValue());
    Enumeration events = eventTable.elements();
    while (events.hasMoreElements()){
      EventInformation eventInfo = (EventInformation)events.nextElement();
      setEventsVisible(eventInfo, visible);
    }
    setState(ALL_EVENTS, new Boolean(visible));    
  }

  private void updateEventState(){
    Enumeration events = eventTable.elements();
    boolean allVisible = true;
    while (events.hasMoreElements()){
      EventInformation eventInfo = (EventInformation)events.nextElement();
      if (!eventInfo.visible){
	allVisible = false;
	break;
      }
    }
    setState(ALL_EVENTS, new Boolean(allVisible));
  }

  void updateState(){
    boolean visible = frame.isDebugWindowVisible();
    if (visible)
      setState(DEBUG_WINDOW, Boolean.TRUE);
    else
      setState(DEBUG_WINDOW, Boolean.FALSE);
  }

  void reset(){
    eventList.removeAllElements();
    eventTable.clear();
    updateStructure();
  }

  class EventInformation{
    String name;
    boolean visible = true;
    Vector eventList = new Vector();
  }
}


