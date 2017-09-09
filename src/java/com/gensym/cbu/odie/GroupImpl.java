package com.gensym.cbu.odie;

import java.util.Enumeration;
import java.util.Vector;
import java.util.Date;

class GroupImpl implements java.io.Serializable, Group 
{
  String groupName;
  String description;
  Vector eventTypes;
  
  public GroupImpl (String groupName) 
  {
    this(groupName, "");
  }

  public GroupImpl (String groupName, String description) 
  {
    this(groupName, description, null);
  }

  public GroupImpl (String groupName, String description, Vector eventTypes) 
  {
    setGroupName(groupName);
    setDescription(description);
    if (eventTypes == null)
      this.eventTypes = new Vector();
    else
      this.eventTypes = eventTypes;
  }

  @Override
  public String getGroupName()
  {
    return groupName;
  }

  @Override
  public void setGroupName(String groupName)
  {
    if( groupName == null || groupName == "")
      this.groupName = "group" + new Date();
    else
      this.groupName  = groupName;
  }

  @Override
  public String getDescription()
  {
    return description;
  }

  @Override
  public void setDescription(String description)
  {
    if (description == null)
      this.description = "";
    else 
      this.description = description;
  }

  @Override
  public void addEventType(String eventType)
  {
    if(eventTypes.contains(eventType) == false)
      {
	eventTypes.add(eventType);
      }
  }
    
  @Override
  public void removeEventType(String eventType)
  {
    eventTypes.remove(eventType);
  }

  @Override
  public Enumeration getEventTypes()
  {
    return eventTypes.elements();
  }
}
