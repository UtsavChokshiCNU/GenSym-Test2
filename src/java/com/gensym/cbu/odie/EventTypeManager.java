package com.gensym.cbu.odie;

import java.util.Enumeration;

/** The EventTypeManager serves as the facility to define the valid eventTypes that can be 
 * subscribed to and published in a Manager. A description of each eventType is recorded with each eventType
 * to serve as documentation and help when subscribing or publishing an event.
 */
interface EventTypeManager
{
  public String getDescription (String eventType) throws EventTypeDoesNotExistException;

  public void setDescription (String eventType, String description, boolean overwrite) 
       throws EventTypeAlreadyDefinedException;

  public void removeDescription (String eventType) throws EventTypeDoesNotExistException;

  public Enumeration getEventTypes();

  public boolean isEventTypeDefined(String eventType);
}
