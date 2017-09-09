package com.gensym.beaneditor;

import com.gensym.classtools.*;
import com.gensym.message.Trace;
import java.lang.reflect.*;
import java.beans.Introspector;
import java.beans.BeanInfo;
import java.beans.IntrospectionException;
import java.beans.PropertyDescriptor;
import java.util.Vector;

public class HookupArgument implements java.io.Serializable
{
  //add UUID

  static final int UNSPECIFIED = 0;
  static final int CONSTANT_INT = 1;
  static final int CONSTANT_LONG = 2;
  static final int CONSTANT_CHAR = 3;
  static final int CONSTANT_SHORT = 4;
  static final int CONSTANT_BYTE = 5;
  static final int CONSTANT_DOUBLE = 6;
  static final int CONSTANT_FLOAT = 7;
  static final int CONSTANT_BOOLEAN = 8;
  static final int CONSTANT_NULL = 9;
  static final int CONSTANT_STRING = 10;
  static final int CONSTANT_SYMBOL = 11;
  static final int OBJECT_ITSELF = 21;
  static final int OBJECT_PROPERTY = 22;

  String name;
  Class type;
  int valueType = UNSPECIFIED;
  String objectName; // "source", "target", "event", or some friend name
  String propertyName;
  String constantExpression;  

  HookupArgument(String name, Class type)
  {
    this.name = name;
    this.type = type;
  }

  String getErrorIfAny(HookupCall call,
		       Class eventType)
		       
  {
    try {
      generateCode(call,null,eventType,"dummyVarName");
    } catch (Exception e)
      {
	return e.getMessage();
      }
    return null;
  }

  Expression generateCode(HookupCall call,
			  ClassInfo hookupClassInfo,
			  Class eventType,
			  String eventObjectVariableName)
  {
    Class sourceType = call.sourceWrapper.getBean().getClass();
    Class targetType = call.targetWrapper.getBean().getClass();
    String[] knownBeanNames = call.sourceWrapper.knownBeanNames();
    Class[] knownBeanClasses = call.sourceWrapper.knownBeanClasses();
    String hookupClassName;
    if (hookupClassInfo != null) 
      hookupClassName = hookupClassInfo.getClassName();
    else
      hookupClassName = "com.gensym.beansruntime.DummyHookup";
    try {
      switch (valueType)
	{
	case UNSPECIFIED:
	  throw new IllegalStateException("No Argument Specified");
	case OBJECT_ITSELF:
	case OBJECT_PROPERTY:
	  Expression objectExpression = null;
	  Class objectType = null;
	  if (objectName == null)
	    throw new IllegalArgumentException("no object name specified");
	  else if (objectName.equals("event"))
	    {
	      Variable variableExpression
		= new Variable(eventObjectVariableName,"Ljava/lang/Object;");
	      objectType = eventType;
	      objectExpression 
		= new Cast(HookupFactory.descriptorForType(eventType),
			   variableExpression);
	    }
	  else if (objectName.equals("target"))
	    {
	      objectType = targetType;
	      objectExpression
		= new Cast(HookupFactory.descriptorForType(targetType),
			   new FieldRef("com.gensym.beansruntime.Hookup",
					"target",
					"Ljava/lang/Object;"));
	    }
	  else if (objectName.equals("source"))
	    {
	      objectType = sourceType;
	      objectExpression
		= new Cast(HookupFactory.descriptorForType(sourceType),
			   new FieldRef("com.gensym.beansruntime.Hookup",
					"source",
					"Ljava/lang/Object;"));
	    }
	  else
	    {
	      int i,len = knownBeanNames.length;
	      for (i=0; i<len; i++)
		if (objectName.equals(knownBeanNames[i]))
		  {
		    objectType = knownBeanClasses[i];
		    objectExpression
		      = new FieldRef(hookupClassName,
				     knownBeanNames[i],
				     HookupFactory.descriptorForType(objectType));
		    break;
		  }
	      if (objectExpression == null)
		throw new RuntimeException("no object found for name");
	    }
	  if (valueType == OBJECT_PROPERTY)
	    {
	      // use bean property getter on object
	      // with appropriate casts
	      if (propertyName == null)
		throw new IllegalArgumentException("no property specified");
	      else
		{
		  BeanInfo beanInfo = null;
		  try {
		    beanInfo = Introspector.getBeanInfo(objectType);
		  } catch (IntrospectionException ie)
		    {
		      throw new IllegalArgumentException("object not a proper bean");
		    }
		  PropertyDescriptor[] propertyDescs = beanInfo.getPropertyDescriptors();
		  int i,len = propertyDescs.length;
		  for (i=0; i<len; i++)
		    {
		      PropertyDescriptor property = propertyDescs[i];
		      if (property.getName().equals(propertyName))
			{
			  Method reader = property.getReadMethod();
			  Class propertyType = property.getPropertyType();
			  if (reader == null)
			    throw new IllegalArgumentException("unreadable property");
			  else if (type.isAssignableFrom(propertyType))
			    {
			      MethodRef methodRef
				= new MethodRef(objectType.getName(),
						reader.getName(),
						"()"+
						HookupFactory.descriptorForType(propertyType));
			      return
				new MethodCall(objectExpression,
					       methodRef,
					       new Expression[0],
					       RuntimeConstants.MTH_CALL_VIRTUAL);
			    }
			  else
			    throw new IllegalArgumentException("property type mismatch");
			}
		    }
		  throw new IllegalArgumentException("unknown property name");
		}
	    }
	  else
	    return new Cast(HookupFactory.descriptorForType(type),objectExpression);
	case CONSTANT_INT:
	  return new Value(Integer.parseInt(constantExpression));
	case CONSTANT_LONG:
	  return new Value(Long.parseLong(constantExpression));
	case CONSTANT_CHAR:
	  if (constantExpression.length() == 1)
	    return new Value((char)constantExpression.charAt(0));
	  else
	    throw new IllegalArgumentException("specify one and only one character");
	case CONSTANT_SHORT:
	  return new Value(Short.parseShort(constantExpression));
	case CONSTANT_BYTE:
	  return new Value(Byte.parseByte(constantExpression));
	case CONSTANT_DOUBLE:
	  return new Value(Double.valueOf(constantExpression).doubleValue());
	case CONSTANT_FLOAT:
	  return new Value(Float.valueOf(constantExpression).floatValue());
	case CONSTANT_BOOLEAN:
	  if (constantExpression.equalsIgnoreCase("true"))
	    return new Value(true);
	  else if (constantExpression.equalsIgnoreCase("false"))
	    return new Value(false);
	  else
	    throw new IllegalArgumentException("bad syntax for boolean");
	case CONSTANT_NULL:
	  return new Value(null);
	case CONSTANT_STRING:
	  return new Value(constantExpression);
	case CONSTANT_SYMBOL:
	  return null;
	default:
	  throw new RuntimeException("NYI");
	}
    } catch (ClassException e)
      {
	Trace.exception(e);
	throw new RuntimeException("Internal HookupFactory failure");
      }
  }

  private Class getObjectClass(HookupCall call, Class eventType, String objectName)
  {
    Class sourceType = call.sourceWrapper.getBean().getClass();
    Class targetType = call.targetWrapper.getBean().getClass();
    String[] knownBeanNames = call.sourceWrapper.knownBeanNames();
    Class[] knownBeanClasses = call.sourceWrapper.knownBeanClasses();
    Class objectType = null;
    if (objectName.equals("event"))
      return eventType;
    else if (objectName.equals("target"))
      return targetType;
    else if (objectName.equals("source"))
      return sourceType;
    else
      {
	int i,len = knownBeanNames.length;
	for (i=0; i<len; i++)
	  if (objectName.equals(knownBeanNames[i]))
	    return knownBeanClasses[i];
	return null;
      }
  }

  HookupChoices[] getHookupChoices(HookupCall call, Class eventType)
  {
    Vector choiceVector = new Vector();
    addChoicesForObject(call,choiceVector,eventType,"event");
    addChoicesForObject(call,choiceVector,eventType,"target");
    addChoicesForObject(call,choiceVector,eventType,"source");
    String[] knownBeanNames = call.sourceWrapper.knownBeanNames();
    int i,len = knownBeanNames.length;
    for (i=0; i<len; i++)
      addChoicesForObject(call,choiceVector,eventType,knownBeanNames[i]);
    HookupChoices[]  result = new HookupChoices[choiceVector.size()];
    choiceVector.copyInto(result);
    return result;
  }

  private void addChoicesForObject(HookupCall call, Vector choiceVector,
				   Class eventType, String objectName)
  {
    Class c = getObjectClass(call,eventType,objectName);
    if (c != null)
      {
	HookupChoices choices = new HookupChoices();
	choices.objectName = objectName;
	if (type.isAssignableFrom(c))
	  choices.isObjectItselfApplicable = true;
	BeanInfo beanInfo = null;
	try {
	  beanInfo = Introspector.getBeanInfo(c);
	} catch (IntrospectionException ie)
	  {
	    throw new IllegalArgumentException("object not a proper bean");
	  }
	PropertyDescriptor[] propertyDescs = beanInfo.getPropertyDescriptors();
	int i,len = propertyDescs.length;
	Vector propertyVector = new Vector();
	for (i=0; i<len; i++)
	  {
	    PropertyDescriptor property = propertyDescs[i];
	    Method reader = property.getReadMethod();
	    Class propertyType = property.getPropertyType();
	    if (reader != null &&		
		type.isAssignableFrom(propertyType))
	      propertyVector.addElement(property.getName());
	  }
	choices.applicableProperties = new String[propertyVector.size()];
	propertyVector.copyInto(choices.applicableProperties);
	choiceVector.addElement(choices);
      }
  }
    
  String[] getApplicablePropertyNames(String objectName)
  {
    return new String[0];
  }

  boolean isObjectItselfApplicable(String objectName)
  {
    return false;
  }

  @Override
  public String toString(){
    return getClass().getName() + "(" + name +" "+ type +" "+ valueType +" "+ objectName +" "+ propertyName +" "+ constantExpression +")";
  }
}









