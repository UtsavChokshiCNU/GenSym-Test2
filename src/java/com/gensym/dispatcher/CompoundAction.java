package com.gensym.dispatcher;

import java.lang.reflect.*;
import java.util.*;
/**
 * CompoundAction
 */

public class CompoundAction extends Action

{

  private Vector nodes = new Vector();
  
  public CompoundAction()
  {
  }

  public void addNode(Node node)
  {
    nodes.addElement(node);
  }

  @Override
  public Object invoke(DispatchTable table)
       throws IllegalAccessException,
	 IllegalArgumentException,
	 InvocationTargetException
  {
    Enumeration e = nodes.elements();
    Node node; Action action;
    Object returnValue = null;
    while (e.hasMoreElements()) {
      action = null;
      node = (Node)e.nextElement();
      if (node instanceof Decision)
	action = table.lookupAction((Decision)node);
      else if (node instanceof Action)
	action = (Action)node;
      if (action != null)
	returnValue = action.invoke(table);
    }
    return returnValue;
  }

  @Override
  public String toString()
  {
    String str="";
    Enumeration e = nodes.elements();
    Node node = null;
    while (e.hasMoreElements()) {
      if (node != null)
	str+=node.toString()+"\n";
      node = (Node)e.nextElement();
    }
    if (false)//node instanceof Action)
      return str + "return " + node.toString();
    else
      return str + node.toString();
  }
}
