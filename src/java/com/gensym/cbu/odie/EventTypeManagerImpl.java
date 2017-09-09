package com.gensym.cbu.odie;

import java.util.Hashtable;
import java.util.Enumeration;
import java.io.Serializable;

/** This is the default implementation of the EventTypeManager interface.
 */
class EventTypeManagerImpl implements Serializable, EventTypeManager
{
  Hashtable eventTypes = new Hashtable();

  public EventTypeManagerImpl()
  {
    super();
  }

  @Override
  public String getDescription (String eventType) throws EventTypeDoesNotExistException
  {
    if (!isEventTypeDefined(eventType))
	throw new EventTypeDoesNotExistException ("Event Type (" + eventType + ") is not defined");

    return (String)eventTypes.get(eventType);
  }

  @Override
  public void setDescription (String eventType, String description, boolean overwrite) 
       throws EventTypeAlreadyDefinedException
  {
    if (isEventTypeDefined(eventType)) 
      {
	if (!overwrite) 
	    throw new EventTypeAlreadyDefinedException ("Event Type (" + eventType
							+ ") is already defined with description = " 
							+ eventTypes.get(eventType));

	eventTypes.remove(eventType);
      }
    eventTypes.put(eventType, description);
  }

  @Override
  public void removeDescription (String eventType) throws EventTypeDoesNotExistException
  {
     if (!isEventTypeDefined(eventType))
	throw new EventTypeDoesNotExistException ("Event Type (" + eventType + ") is not defined");

    eventTypes.remove(eventType);
  }

  @Override
  public Enumeration getEventTypes()
  {
    return eventTypes.keys();
  }

  @Override
  public boolean isEventTypeDefined(String eventType)
  {
    return eventTypes.containsKey(eventType);
  }
}
