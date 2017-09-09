package com.gensym.cbu.odie;

import java.util.Vector;
import com.gensym.denali.common.DenaliRemoteObject;
import java.rmi.*;
import com.gensym.denali.model.Module;

public class OdieTester
{
  public OdieTester()
  {
    super();
  }

  String name = "";

  public String getName ()
  {
    return name;
  }

  public void setName(String name)
  {
    this.name = name;
  }

  String managerName = "";

  public String getManagerName ()
  {
    return managerName;
  }

  public void setManagerName(String managerName)
  {
    this.managerName = managerName;
  }

  String eventType = "";

  public String getEventType ()
  {
    return eventType;
  }

  public void setEventType(String eventType)
  {
    this.eventType = eventType;
  }
  
  boolean overwrite = true;

  public boolean getOverwrite ()
  {
    return overwrite;
  }

  public void setOverwrite(boolean overwrite)
  {
    this.overwrite = overwrite;
  }

  String eventTypeDescription = "";
  
  public String getEventTypeDescription ()
  {
    return eventTypeDescription;
  }

  public void setEventTypeDescription(String eventTypeDescription)
  {
    this.eventTypeDescription = eventTypeDescription;
  }

  String targetId = "";

  public String getTargetId ()
  {
    return targetId;
  }

  public void setTargetId(String targetId)
  {
    this.targetId = targetId;
  }

  String senderId = "";

  public String getSenderId ()
  {
    return senderId;
  }

  public void setSenderId(String senderId)
  {
    this.senderId = senderId;
  }

  String messageText = "";

  public String getMessageText ()
  {
    return messageText;
  }

  public void setMessageText(String messageText)
  {
    this.messageText = messageText;
  }

  String additionalText = "";

  public String getAdditionalText ()
  {
    return additionalText;
  }

  public void setAdditionalText(String additionalText)
  {
    this.additionalText = additionalText;
  }

  //test functions
  public void defineEventTypeTest() throws RemoteException, EventTypeAlreadyDefinedException
  {
    System.out.println("EventTypeTest");	
    Manager manager = (Manager)(Utilities.getUniqueGraphElementWithinModule(managerName, this).getBean());
    if (manager == null)
      System.out.println("Manager lookup failed in defineEventTypeTest");
    else
      {
	System.out.println("about to call manager fn with :" + 
			   eventType + ", " + 
			   eventTypeDescription + ", " +
			   overwrite);
	manager.setEventTypeDescription(eventType, eventTypeDescription, overwrite);
      }
  }

  public void publishNewEventTest() throws RemoteException, EventTypeDoesNotExistException
  {
    Manager manager = (Manager)(Utilities.getUniqueGraphElementWithinModule(managerName, this).getBean());
    if (manager == null)
      System.out.println("Manager lookup failed in publishNewEventTest");
    else
      manager.publishNewEvent(eventType,
			      targetId,
			      senderId,
			      messageText,
			      additionalText,
			      null,
			      null,
			      null); 
  }
}
    
