package com.gensym.cbu.odie;

import java.util.Enumeration;

interface Group
{
  public String getGroupName();

  public void setGroupName(String groupName);

  public String getDescription();

  public void setDescription(String description);

  public void addEventType(String eventType);
    
  public void removeEventType(String eventType);

  public Enumeration getEventTypes();
}
