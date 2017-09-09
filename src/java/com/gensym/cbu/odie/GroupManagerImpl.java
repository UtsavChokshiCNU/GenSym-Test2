package com.gensym.cbu.odie;

import java.util.Hashtable;
import java.util.Enumeration;
import java.io.Serializable;

/** This is the default implementation of the GroupManager interface.
 */
class GroupManagerImpl implements Serializable, GroupManager
{
  Hashtable groups = new Hashtable();

  @Override
  public String getDescription (String groupName) throws GroupDoesNotExistException
  {
    if (groups.contains(groupName))
      {
	Group group = (Group)groups.get(groupName);
	return group.getDescription();
      }
    else
      throw new GroupDoesNotExistException("No group with name " + groupName + " exists");
  }

  @Override
  public void setDescription (String groupName, String description) 
       throws GroupDoesNotExistException
  {
    if (groups.contains(groupName))
      {
	Group group = (Group)groups.get(groupName);
	group.setDescription(description);
      }
    else
      throw new GroupDoesNotExistException("No group with name " + groupName + " exists");
  }

  @Override
  public Enumeration getGroupNames()
  {
    return groups.keys();
  }

  @Override
  public boolean isGroupDefined(String groupName)
  {
    return groups.contains(groupName);
  }
}
