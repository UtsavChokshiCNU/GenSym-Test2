package com.gensym.beaneditor;

import java.awt.Image;
import java.awt.Component;
import java.awt.Point;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.beans.*;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.StructuredCommandListener;
import com.gensym.ui.CommandListener;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.SubCommand;

class InsertEventConnectionCommand implements StructuredCommand{

  private Vector structure, events, listeners;
  private Wrapper currentWrapper;
  private EditorFrame frame;
  private String label;
  private boolean notify;
  private int newEventX, newEventY;
  private boolean locationSpecified = false;
  private static final int portSize = 10;//16!!

  InsertEventConnectionCommand(EditorFrame frame, String label, boolean notify){
    this.frame = frame;
    listeners = new Vector();
    structure = new Vector(1);
    events = new Vector();
    this.label = label;
    this.notify = notify;
    SubCommand eventsSubCmd = new SubCommand(label, events);
    structure.addElement(eventsSubCmd);
  }

  @Override
  public void actionPerformed(ActionEvent actionEvent){
    String cmdKey = actionEvent.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey))
      throw new IllegalStateException("Command is unavailable");
    doAddPort(cmdKey);
  }

  @Override
  public boolean isAvailable(String key){
    boolean available = false;
    BeanCanvas canvas = frame.getCanvas();
    if (canvas != null && frame.application.inDesignMode()){
      if (frame.getBeanEditTool().selectionCount() == 1){
	Component[] selection = frame.getBeanEditTool().getSelection();
	if (selection[0] instanceof  Wrapper && ((Wrapper)selection[0]).bean != null){
	  Wrapper wrapper = (Wrapper)selection[0];
	  if (events.size() > 0)
	    available = true;
	}
      }
    }
    return available;
  }

  @Override
  public Boolean getState(String key){
    return null;
  }

  @Override
  public String getDescription(String key, String type){
    return key;
  }

  @Override
  public Image getIcon(String key, String size){
    return null;
  }

  @Override
  public Vector getStructuredKeys(){
    return structure;
  }

  @Override
  public boolean isImmediate(String key){
    return true;
  }

  @Override
  public void addCommandListener(CommandListener l){}
  @Override
  public void removeCommandListener(CommandListener l){}
  @Override
  public void addStructuredCommandListener(StructuredCommandListener l){
    listeners.addElement(l);
  }
  @Override
  public void removeStructuredCommandListener(StructuredCommandListener l){
    listeners.removeElement(l);
  }

  @Override
  public String[] getKeys(){
    return null;
  }


  void setPosition(int x, int y){
    newEventX = x;
    newEventY = y;
    locationSpecified = true;
  }

  void updateCurrentWrapper(){
    Wrapper wrapper = null;
    if (frame.getBeanEditTool().selectionCount() == 1){
      Component[] selection = frame.getBeanEditTool().getSelection();
      if (selection[0] instanceof  Wrapper && ((Wrapper)selection[0]).bean != null){
	wrapper = (Wrapper)selection[0];
      }
    }
    updateCurrentWrapper(wrapper);
  }

  void updateCurrentWrapper(Wrapper wrapper){ 
    if (wrapper == null){
      events.removeAllElements();
      currentWrapper = wrapper;
      notifyStructureChanged();
      return;
    }

    Object element = wrapper.getBean();
    Class clazz = element.getClass();

    //re-build structure
    currentWrapper = wrapper;
    events.removeAllElements();
    Preferences preferences = Preferences.currentPreferences;
    try 
      {
	BeanInfo beanInfo = Introspector.getBeanInfo(clazz);
	
	EventSetDescriptor[] eventSetDescriptors 
	  = beanInfo.getEventSetDescriptors();
	
	int i, len = eventSetDescriptors.length;
	for (i=0; i<len ; i++){
	  EventSetDescriptor esd = eventSetDescriptors[i];
	  if (preferences.isExpertMode() ||
	      !esd.isExpert())
	    {
	      MethodDescriptor[] methodDescriptors 
		= esd.getListenerMethodDescriptors();

	      Vector eventList = new Vector();
	      for (int j = 0 ; j<methodDescriptors.length ; j++){
		MethodDescriptor mDesc = methodDescriptors[j];
		eventList.addElement(mDesc.getName());
	      }
	      SubCommand subCmd = new SubCommand(esd.getName(), eventList);
	      events.addElement(subCmd);
	    }
	}
      } catch (IntrospectionException exception){ 
	exception.printStackTrace();
      }
      notifyStructureChanged();
  }


  /**
   * Dispatches a CommandEvent event to listeners.
   */
  protected void notifyStructureChanged(){
    if (!notify) return;
    CommandEvent e = new CommandEvent(this, CommandEvent.STRUCTURE_CHANGED, null);
    Vector l;
    synchronized(this) {l = (Vector)listeners.clone();}
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      StructuredCommandListener listener = 
	((StructuredCommandListener)dispatchList.nextElement());
	listener.commandStructureChanged(e);
    }
  }  
  

  private void doAddPort(String event){
    BeanCanvas canvas = frame.getCanvas();
    if (canvas.getEventInfo(event, currentWrapper.getBeanClass()) != null){
      Wrapper wrapper = currentWrapper;
      EventInfo eventInfo = canvas.getEventInfo(event, wrapper.getBeanClass());
      Preferences prefs = Preferences.currentPreferences;
      ColorMap map = prefs.getEventColorMapping();
      eventInfo.color = map.getOrAssignColor(event);
      if (!locationSpecified){//force to right-side of bean
	Point location = wrapper.getLocation();
	newEventX = location.x + wrapper.getSize().width;
	newEventY = location.y + (portSize/2);
      }
      Port port = new Port(wrapper, eventInfo, Color.lightGray, false,
			   newEventX, newEventY, portSize, portSize);
      canvas.addElement(port);
      wrapper.setPortPosition(port, newEventX, newEventY);
      port.addOutputConnection(Port.defaultStubLength);
      frame.updateViewMenuForAdd(port);
    }
  }

}












