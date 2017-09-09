package com.gensym.rules;

import java.util.EventObject;
import java.util.Vector;
import java.rmi.Remote;
import java.io.Serializable;

public class RuleEvent extends EventObject
{ 
  Vector bindingNames;
  Vector boundValues;
  
  public RuleEvent(Object source,
		   Vector bindingNames,
		   Vector boundValues)
  {
    super(source);
    this.bindingNames = bindingNames;
    int i,len = boundValues.size();
    for (i=0; i<len; i++)
      {
	Object value = boundValues.elementAt(i);
	if (!(value instanceof Remote ||
	      value instanceof Serializable))
	  boundValues.setElementAt(null,i);
      }
    this.boundValues = boundValues;
  }
}
