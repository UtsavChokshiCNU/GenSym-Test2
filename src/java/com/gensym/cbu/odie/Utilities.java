package com.gensym.cbu.odie;

import java.rmi.*;

import com.gensym.denali.model.GraphElement;
import com.gensym.denali.model.ServerImpl;
import com.gensym.denali.model.Module;

public class Utilities
{
  public static GraphElement getUniqueGraphElementWithinModule(String name, Object bean) throws RemoteException
  {
    //    System.out.println("Finding unique graph element whose name is (" + name +
    //	       ") and in the same module as (" + bean + ")");
    GraphElement[] elements = ServerImpl.getGraphElementsContaining(bean);
    if (elements.length == 1 &&
	elements[0] instanceof GraphElement)
      {
	GraphElement element = (GraphElement)elements[0];
	//	System.out.println("Containing Element = (" + element + ")");
	Module module = element.getModule();
	//	System.out.println("module = (" + module + ")");
	GraphElement target = (GraphElement)module.getNamedObject(name);
	//	System.out.println("target = (" + target + ")");
	return target;
      }
    else
      throw new IllegalArgumentException("bean "+bean+" is in 0 or 2 or more element");
  }
}

