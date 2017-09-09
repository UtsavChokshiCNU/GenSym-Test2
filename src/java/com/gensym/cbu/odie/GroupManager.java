package com.gensym.cbu.odie;

import java.util.Enumeration;

interface GroupManager
{
  public String getDescription (String groupName) throws GroupDoesNotExistException;

  public void setDescription (String groupName, String description) 
       throws GroupDoesNotExistException;

  public Enumeration getGroupNames();

  public boolean isGroupDefined(String groupName);
}
