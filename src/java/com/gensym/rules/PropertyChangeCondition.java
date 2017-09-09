package com.gensym.rules;

import com.gensym.classtools.*;
import java.lang.reflect.*;
import java.beans.PropertyChangeEvent;
import java.util.EventObject;
import java.util.Vector;

public class PropertyChangeCondition extends Condition
{
  String propertyName;
  String propertyValueBindingName;

  public PropertyChangeCondition(String bindingName, String className, String propertyName)
  {
    this(bindingName,className,propertyName,null);
  }

  public PropertyChangeCondition(String bindingName, String className, String propertyName,
				 String propertyValueBindingName)
  {
    super(bindingName,className,"propertyChange");
    this.propertyName = propertyName;
    this.propertyValueBindingName = propertyValueBindingName;
  }

  @Override
  Expression makeKeyBuilderExpression(Variable eventVariable)
       throws ClassException
  {
    try 
      {
	Value prefix 
	  = new Value(eventSetDescriptor.getName()+listenerMethod.getName());
	Cast propertyChangeEvent
	  = new Cast("Ljava/beans/PropertyChangeEvent;",eventVariable);
	MethodRef methodRef = new MethodRef("java.beans.PropertyChangeEvent",
					    "getPropertyName",
					    "()Ljava/lang/String;");
	MethodCall call = new MethodCall(propertyChangeEvent,
					 methodRef,
					 new Expression[0],
					 RuntimeConstants.MTH_CALL_VIRTUAL);
	return new OperatorCall("+",
				new Expression[] { prefix, call });
      }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("G2Script Internal Failure");
      }
  }
  
  @Override
  String getOrMakeKey()
  {
    return eventSetDescriptor.getName()+listenerMethod.getName()+propertyName;
  }

  @Override
  void extendBindingsIfNecessary(EventObject event,
				 Vector bindingNames,
				 Vector boundValues)
  {
    if (propertyValueBindingName != null)
      {
	bindingNames.addElement(propertyValueBindingName);
	boundValues.addElement(((PropertyChangeEvent)event).getNewValue());
      }
  }

  @Override
  void retractBindingsIfNecessary(EventObject event,
				  Vector bindingNames,
				  Vector boundValues)
  {
    if (propertyValueBindingName != null)
      {
	int index = bindingNames.size() - 1;
	bindingNames.removeElementAt(index);
	boundValues.removeElementAt(index);
      }
  }


  @Override
  Object getDomainValue(EventObject event)
  {
    return event.getSource();
  }

  @Override
  public String toString()
  {
    return "<PropertyChangeCondition binding="+bindingName+
      " class="+className+" propName="+propertyName+">";
  }
}
