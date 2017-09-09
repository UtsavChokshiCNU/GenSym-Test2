package com.gensym.cbu.odieeventfilterlanguage;

import com.gensym.denali.model.*;
import java.rmi.*;
import java.util.Enumeration;
import java.util.Stack;
import java.util.Hashtable;
import java.util.Vector;

public class EventFilterSchematicImpl extends SchematicImpl
{
  transient SharedDefinitionReference[] commands;
  transient boolean commandsAreCached = false;
  static boolean trace = true;

  public EventFilterSchematicImpl()
       throws RemoteException
  {
    super();
    System.out.println("Creating an EventFilterSchematicImpl"); 
  }

  public EventFilterSchematicImpl(Object parent, String name)
       throws RemoteException
  {
    super(parent,name);
    System.out.println("Creating an EventFilterSchematicImpl"); 
  }

  private void setupCommands()
       throws RemoteException
  {
    System.out.println("Setting up commands for a EventFilterSchematicImpl");
    Module parent = getModule();
    JavaStatement js1 
      = new JavaStatement( "((com.gensym.cbu.odieeventfilterlanguage.EventFilterSchematicImpl)"+
			   "appContainer).compile();");
    
    JavaCommand command = new JavaCommand ( new String[] { "compile"},
                                            new JavaStatement[] { js1 },
					    "com.gensym.cbu.odieeventfilterlanguage",
					    "EventFilterSchematicMenuLabels");

    try {
      parent.setSharedDefinition ("EventFilterSchematicCommands", command);
      commands 
	= new SharedDefinitionReference[] { new SharedDefinitionReference(parent.getName(),
									  "EventFilterSchematicCommands")};
    } catch (RemoteException e)
      {
	System.out.println("failed to set up commands");
	e.printStackTrace();
      }
  }

  protected SharedDefinitionReference[] getCommandReferences()
       throws RemoteException
  {
    if (!commandsAreCached)
      {
	setupCommands();
	commandsAreCached = true;
      }
    return commands;
  }

  public void compile()
       throws RemoteException
  {
    // 1 Find the (unique) start state
    Node startNode = null;
    String booleanExpression;

    if (trace)
      System.out.println("compiling...");
    Enumeration items = getItems();
    while (items.hasMoreElements())
      {
	RemoteItem item = (RemoteItem)items.nextElement();
	if (item instanceof Node)
	  {
	    Object bean = ((Node)item).getBean();
	    if (bean instanceof PriorityBlock)
	      {
		PriorityBlock priorityBlock = (PriorityBlock)bean;
		if (trace)
		  System.out.println("priority node found with priority = " + priorityBlock.getPriority());
		if (startNode != null)
		  throw new RuntimeException("duplicate start states");
		else
		  startNode = (Node)item;
	      }
	  }
      }
    if (startNode == null)
      throw new RuntimeException("no start state found");

    booleanExpression = getBooleanExpression(startNode);
    booleanExpression = new String(booleanExpression + ")");
    System.out.println(booleanExpression);
  }

  String getBooleanExpression(Node currentNode) throws RemoteException
  {
    StringBuffer buffer = new StringBuffer();

    EventFilterBlock eventFilterBlock = (EventFilterBlock)currentNode.getBean();
    buffer.append(eventFilterBlock.booleanExpression());

    Enumeration ports = currentNode.getPorts();
    while ( ports.hasMoreElements())
      {
	Port port = (Port)ports.nextElement();
	if (port.isInput()) continue;

	Connection connection = port.getConnection();
	
	Terminal output = connection.getOutput();
	if (!(output instanceof Port)) continue;

	Node nextNode = ((Port)output).getNode();

	buffer.append(getBooleanExpression(nextNode));
      }

    return buffer.toString();
  }
	
}
