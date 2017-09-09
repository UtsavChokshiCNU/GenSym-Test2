package com.gensym.rules;

import com.gensym.classtools.*;
import java.lang.reflect.*;
import java.beans.EventSetDescriptor;
import java.util.Hashtable;
import java.util.Vector;
import java.util.EventObject;

public class Condition implements java.io.Serializable
{
  String className;
  transient Class cachedClass;
  String eventName;
  transient EventSetDescriptor eventSetDescriptor = null;
  transient Method listenerMethod = null;
  transient Rule rule;
  String bindingName;

  // runtime thing that will implement 
  // the desired event adaptation
  transient Class adapterClass;
  transient Object adapter;
  static transient Hashtable conditionsForClass = new Hashtable();

  public Condition(String bindingName, String className, String eventName)
  {
    this.bindingName = bindingName;
    this.className = className;
    this.eventName = eventName;
  }

  boolean canChain()
  {
    return true;
  }

  Class getDomainClass()
       throws ClassNotFoundException
  {
    if (cachedClass == null)
      {
	cachedClass = rule.ruleManager.classManager.findInstanceClass(className);
	//cachedClass = Class.forName(className);
	return cachedClass;
      }
    else
      return cachedClass;
  }

  Expression makeKeyBuilderExpression(Variable eventVariable)
       throws ClassException
  {
    return new Value(eventSetDescriptor.getName()+listenerMethod.getName());
  }

  String getOrMakeKey()
  {
    return eventSetDescriptor.getName()+listenerMethod.getName();
  }

  void noteForClass()
  {
    System.out.println("noting for class "+cachedClass);
    Vector entry = (Vector) conditionsForClass.get(cachedClass);
    if (entry == null)
      {
	entry = new Vector();
	entry.addElement(this);
	conditionsForClass.put(cachedClass,entry);
      }
    else
      {
	entry.addElement(this);
      }
  }

  void extendBindingsIfNecessary(EventObject event,
				 Vector bindingNames,
				 Vector boundValues)
  {

  }

  void retractBindingsIfNecessary(EventObject event,
				  Vector bindingNames,
				  Vector boundValues)
  {

  }

  void unnoteForClass()
  {
    System.out.println("un-noting for class "+cachedClass);
    Vector entry = (Vector) conditionsForClass.get(cachedClass);
    if (entry != null)
      {
	if (entry.size() <= 1)
	  conditionsForClass.remove(cachedClass);
	else
	  entry.removeElement(this);
      }
  }

  Object getDomainValue(EventObject event)
  {
    return event;
  }

  @Override
  public String toString()
  {
    return "<Condition "+eventName+" on "+className+" with binding "+bindingName+">";
  }
}
