package com.gensym.rules;

import java.util.Vector;
import java.util.Hashtable;
import java.lang.reflect.*;

import com.gensym.g2scriptruntime.RegistrationEvent;
import com.gensym.g2scriptruntime.RegistrationListener;

public class RegistrationAdapter implements RegistrationListener
{

  @Override
  public void registerObject(RegistrationEvent e)
  {
    registerOrDeregisterObject(e,true);
  }

  @Override
  public void deregisterObject(RegistrationEvent e)
  {
    registerOrDeregisterObject(e,false);
  }

  public void registerOrDeregisterObject(RegistrationEvent e,boolean register)
  {
    Object o = e.getObject();
    Class keyClass = o.getClass();
    Vector conditionVector = (Vector) Condition.conditionsForClass.get(keyClass);

    while (keyClass != Object.class)
      {
	conditionVector = (Vector) Condition.conditionsForClass.get(keyClass);
	keyClass = keyClass.getSuperclass();
	if (conditionVector != null)
	  break;
      }
 
    if (Rule.debug)
      {
	System.out.println("hashtable "+Condition.conditionsForClass);
	System.out.println((register?"Der":"R")+"egistering "+o+
			   " key class "+keyClass+
			   " conditionVector "+conditionVector);
      }
    if (conditionVector != null)
      {
	int i,size = conditionVector.size();
	for (i=0; i<size ; i++)
	  {
	    Condition condition = (Condition) conditionVector.elementAt(i);
	    Method theMethod
	      = (register?
		 condition.eventSetDescriptor.getAddListenerMethod():
		 condition.eventSetDescriptor.getRemoveListenerMethod());
	    try {
	      if (Rule.debug)
		System.out.println("calling "+(register?"add":"remove")+
				   " listener method "+theMethod+
				   " on "+o+" with "+condition.adapter);
	      theMethod.invoke(o, new Object[] { condition.adapter });
	    } catch (Exception ex)
	      {
		System.out.println("Failed to "+(register?"add":"remove")+
				   " listener");
		ex.printStackTrace();
	      }
	  }
      }
  }


}
